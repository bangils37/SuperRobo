
#include "MainObject.h"

MainObject::MainObject()
{
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    width_frame_=0;
    height_frame_=0;
    status_=-1;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.jump_=0;
    input_type_.up_=0;
    input_type_.down_=0;
    on_ground = false;
    map_x_=0;
    map_y_=0;
    come_back_time=0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if(ret==TRUE)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }

    return ret;
}

void MainObject::set_clip()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0;i<8;i++)
        {
            frame_clip_[i].x=width_frame_ * i;
            frame_clip_[i].y=0;
            frame_clip_[i].w=width_frame_;
            frame_clip_[i].h=height_frame_;
        }
    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if(on_ground)
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("img/player_left_main.png", des);
        }
        else
        {
            LoadImg("img/player_right_main.png", des);
        }
    }
    else
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("img/jump_left_main.png", des);
        }
        else if(status_ == WALK_RIGHT)
        {
            LoadImg("img/jump_right_main.png", des);
        }
        else
        {
            LoadImg("img/jump_right_main.png", des);
        }
    }

    if(input_type_.left_ == 1 ||
       input_type_.right_ == 1 ||
       !on_ground)
    {
        frame_++;
    }
    else
    {
        frame_=0;
    }

    if(frame_>=8)
        frame_=0;

//    cout<<rect_.x<<' '<<rect_.y<<'\n';

    /// Tại sao phải có -map_x_ và -map_y_?
    /// rect_.x, y là vị trí toạ độ góc trái trên của hình ảnh trên màn hình
    /// Nếu không trừ phần map đã đi qua thì màn hình thật sự vẫn có toạ độ trái trên ở vị trí x_pos_=0 và y_pos_0
    /// Nhưng đồ hoạ map chạy theo position của nhân vật nên làm cho đồ hoạ map hiển thị sai sao với map thật
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip_ = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip_, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status_ = WALK_RIGHT;
                input_type_.right_=1;
                input_type_.left_=0;
            }
            break;
        case SDLK_a:
            {
                status_ = WALK_LEFT;
                input_type_.left_=1;
                input_type_.right_=0;
            }
            break;
        case SDLK_SPACE:
            {
                input_type_.jump_=1;
            }
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_d:
            {
                input_type_.right_=0;
                input_type_.left_=0;
            }
            break;
        case SDLK_a:
            {
                input_type_.right_=0;
                input_type_.left_=0;
            }
            break;
        }
    }
//    cout<<input_type_.right_<<' '<<input_type_.left_<<'\n';
}

void MainObject::DoPlayer(Map& map_data)
{
    if(come_back_time > 0)
    {
        come_back_time--;
        if(come_back_time == 0)
        {
            x_pos_=0;
            y_pos_=0;
            x_val_=0;
            y_val_=0;
        }
        return;
    }

    x_val_=0;
    y_val_+=GRAVITY_SPEED;

    if(y_val_>=MAX_FALL_SPEED)
    {
        y_val_=MAX_FALL_SPEED;
    }

    if(input_type_.left_ == 1)
    {
        x_val_ -= PLAYER_SPEED;
    }
    else if(input_type_.right_ == 1)
    {
        x_val_ += PLAYER_SPEED;
    }

    if(input_type_.jump_ == 1)
    {
        if(on_ground)
        {
            y_val_ = -PLAYER_JUMP;
        }
        input_type_.jump_=0;
    }

    CheckToMap(map_data);
//    cout<<map_data.start_x_<<' '<<map_data.start_y_<<'\n';
    CenterEntityOnMap(map_data);
//    cout<<map_data.start_x_<<' '<<map_data.start_y_<<'\n';
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if(map_data.start_x_<0)
    {
        map_data.start_x_=0;
    }
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_=map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = 0;
//    cout<<map_data.start_y_<<'\n';
}

void MainObject::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check horizontal
    int height_min = height_frame_ < TILE_SIZE ?  height_frame_:TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_)/TILE_SIZE;

    y1 = y_pos_ / TILE_SIZE;
    y2 = (y_pos_ + height_min) /TILE_SIZE;

    if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(x_val_>0)
        {
            if(map_data.tile[y1][x2] != BLACK_TILE /*|| map_data.tile[y2][x2] != BLACK_TILE*/)
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if(x_val_ < 0)
        {
            if(map_data.tile[y1][x1] != BLACK_TILE /*|| map_data.tile[y2][x1] != BLACK_TILE*/)
            {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //Check vertical
    int width_min = width_frame_ < TILE_SIZE ? width_frame_:TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + height_frame_) /TILE_SIZE;

    if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(y_val_>0)
        {
            if(map_data.tile[y2][x1] != BLACK_TILE || map_data.tile[y2][x2] != BLACK_TILE)
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= height_frame_;
                y_val_ = 0;
                on_ground = true;
            }
            else
            {
                on_ground = false;
            }
        }
        else if(y_val_<0)
        {
            on_ground = false;
            if(map_data.tile[y1][x1] != BLACK_TILE || map_data.tile[y1][x2] != BLACK_TILE)
            {
                y_pos_ = (y1+1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    if(y_pos_ > map_data.max_y_)
    {
        come_back_time = FRAME_PER_SECOND * 1;
    }
}

void MainObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
