
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"


#define BLACK_TILE 0
#define GRAVITY_SPEED 1.3
#define MAX_FALL_SPEED 17
#define PLAYER_SPEED 8
#define PLAYER_JUMP 25

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clip();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
    void GetPos(int &x, int &y) {x = x_pos_; y = y_pos_;}
    void SetPos(int x, int y) {x_pos_ = x; y_pos_ = y;}
    void SetInput(int x, int y) {input_type_.right_ = x; input_type_.left_ = y;}
    SDL_Rect GetRect() const {return rect_;}
    void CenterEntityOnMap(Map& map_data);
    void Free();

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground;

    int map_x_;
    int map_y_;

    int come_back_time;
};

#endif // MAIN_OBJECT_H_
