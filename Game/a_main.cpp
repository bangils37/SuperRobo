
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "FireBall.h"
#include "DragonObject.h"
#include "TextObject.h"

BaseObject g_background;
BaseObject g_background_menu;
TTF_Font* font_time = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Hello Wolrd",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&&imgFlags))
                success = false;
        }

        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("font/dlxfont_.ttf", 15);
        if(font_time == NULL)
        {
            success = false;
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/Background_main.jpg", g_screen);
    if(ret == false)
        return false;

    return true;
}

int ShowMenu()
{
    bool ret = g_background_menu.LoadImg("img/Menu_main.jpg", g_screen);
    if(ret == false)
        return 1;

    const int nMenu = 2;
    bool selected[nMenu] = {0, 0};
    TextObject text_menu[nMenu];

    text_menu[0].SetPos(600, 400);
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetText("PLAY");
    text_menu[0].LoadFromRenderText(font_time, g_screen);

    text_menu[1].SetPos(600, 450);
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetText("EXIT");
    text_menu[1].LoadFromRenderText(font_time, g_screen);


    SDL_Event m_event;
    while(true)
    {
        g_background_menu.Render(g_screen, NULL);

        for(int i=0;i<nMenu;i++)
        {
            text_menu[i].LoadFromRenderText(font_time, g_screen);
            text_menu[i].RenderText(g_screen);
        }

        int xm;
        int ym;
        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;
                    for(int i=0; i<nMenu; i++)
                    {
                        if(text_menu[i].CheckCollision(xm, ym))
                        {
                                selected[i] = true;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                        else
                        {
                                selected[i] = false;
                                text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;
                    for(int i=0; i<nMenu; i++)
                    {
                        if(text_menu[i].CheckCollision(xm, ym))
                        {
                            return i;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(g_screen);

        for(int i=0; i<nMenu; i++) text_menu[i].Free();
    }
}

void GameEndMenu(bool &is_quit, bool win)
{
    bool ret;
    if(win)
    {
        ret = g_background_menu.LoadImg("img/gamewinning_main.jpg", g_screen);
    }
    else
    {
        ret = g_background_menu.LoadImg("img/gameover_main.jpg", g_screen);
    }
    if(ret == false)
    {
        is_quit = true;
        return;
    }

    const int nMenu = 2;
    bool selected[nMenu] = {0, 0};
    TextObject text_menu[nMenu];

    text_menu[0].SetPos(580, 400);
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetText("REPLAY");
    text_menu[0].LoadFromRenderText(font_time, g_screen);

    text_menu[1].SetPos(600, 450);
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].SetText("EXIT");
    text_menu[1].LoadFromRenderText(font_time, g_screen);


    SDL_Event m_event;
    while(true)
    {
        g_background_menu.Render(g_screen, NULL);

        for(int i=0;i<nMenu;i++)
        {
            text_menu[i].LoadFromRenderText(font_time, g_screen);
            text_menu[i].RenderText(g_screen);
        }

        int xm;
        int ym;
        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                {
                    is_quit = true;
                    return;
                }
                break;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;
                    for(int i=0; i<nMenu; i++)
                    {
                        if(text_menu[i].CheckCollision(xm, ym))
                        {
                                selected[i] = true;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                        else
                        {
                                selected[i] = false;
                                text_menu[i].SetColor(TextObject::BLACK_TEXT);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;
                    for(int i=0; i<nMenu; i++)
                    {
                        if(text_menu[i].CheckCollision(xm, ym))
                        {
                            is_quit = i;
                            return;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(g_screen);

        for(int i=0; i<nMenu; i++) text_menu[i].Free();
    }
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    int start_time = 0;
    int time_one_frame = 1000/FRAME_PER_SECOND;
    int deltaTime = 0;
    int time[2] = {0, 0};

    if(InitData() == false)     // Khởi tạo DATA
        return -1;

    if(LoadBackground() == false)       // Load Background vào
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/main_map.dat");       // Load map (raw) vào
    game_map.LoadTiles(g_screen);               // Load map (image) ra mh

    /// Warrior
    MainObject p_player;
    p_player.LoadImg("img/player_right_main.png", g_screen);     // Load ảnh nhân vật vào
    p_player.set_clip();                                    // Load các frame nhân vật vào

    /// FireBalls
    FireBall ball[10];
    for(int i=0;i<10;i++)
    {
        ball[i].LoadImg("img/fire_ball_main.png", g_screen);
        ball[i].set_clip();
        ball[i].SetPos(SCREEN_WIDTH + 10, i*TILE_SIZE);
    }

    /// Dragons
    DragonObject dragon[5];
    for(int i=0;i<5;i++)
    {
        dragon[i].LoadImg("img/dragon_left_main.png", g_screen);
        dragon[i].set_clip();
        dragon[i].SetPos(SCREEN_WIDTH + 10, SCREEN_HEIGHT/2);
    }

    /// Time text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    /// HP text
    int hp_ = 3;
    TextObject HP_Players;
    HP_Players.SetColor(TextObject::WHITE_TEXT);

    bool is_quit = ShowMenu();
    while(!is_quit)
    {
        fps_timer.start();

        while(SDL_PollEvent(&g_event)!=0)                       // Get tương tác phím chuột
        {
            if(g_event.type == SDL_QUIT)
                is_quit = true;

            p_player.HandelInputAction(g_event, g_screen);      // Nhận phím
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);   // Transferent màu
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);                    // Load background ra mh

        Map map_data = game_map.GetMap();

        /// Player
        int player_pos_x;
        int player_pos_y;

        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);// Gán map
        p_player.DoPlayer(map_data);                            // Thay đổi vị trí nhân vật và map khi hành động
        p_player.Show(g_screen);                                // Load nhân vật ra mh
        p_player.GetPos(player_pos_x, player_pos_y);

        /// Check Victory
        if(player_pos_x > 5200 && player_pos_y == 129)
        {
            p_player.SetInput(0, 0);
            hp_ = 3;
            GameEndMenu(is_quit, true);
            if(is_quit)
            {
                close();
                return 0;
            }
            else
            {
                start_time = SDL_GetTicks()/1000;
                p_player.SetPos(0, 0);
                for(int i=0;i<5;i++) dragon[i].isDeath = true;
                for(int i=0;i<10;i++) ball[i].moving = false;
            }
        }

        /// Random Pick Fireball
        time[0] += deltaTime;
        if(time[0] >= 700)
        {
            time[0] = 0;
            int idx_ = rand() % 10;
            ball[idx_].moving = true;
        }
        /// Random Pick Dragon
        time[1] += deltaTime;
        if(time[1] >= 4000)
        {
            time[1] = 0;
            int idx_ = rand() % 5;
            if(dragon[idx_].isDeath)
            {
                dragon[idx_].isDeath = false;
            }
        }

        /// FireBall
        for(int i=0;i<10;i++)
        {
            ball[i].SetMapXY(map_data.start_x_, map_data.start_y_);
            ball[i].Move();
            ball[i].Show(g_screen);
            if(SDLCommonFunc::CheckCollision(ball[i].GetRect(), p_player.GetRect()))
            {
                --hp_;
                if(hp_)
                {
                    ball[i].moving = false;
                }
                else
                {
                    p_player.SetInput(0, 0);
                    hp_ = 3;
                    GameEndMenu(is_quit, false);
                    if(is_quit)
                    {
                        close();
                        return 0;
                    }
                    else
                    {
                        start_time = SDL_GetTicks()/1000;
                        p_player.SetPos(0, 0);
                        for(int i=0;i<5;i++) dragon[i].isDeath = true;
                        for(int i=0;i<10;i++) ball[i].moving = false;
                    }
                }
            }
        }
        /// Dragon
        for(int i=0;i<5;i++)
        {
            dragon[i].SetTarget(player_pos_x, player_pos_y);
            dragon[i].SetMapXY(map_data.start_x_, map_data.start_y_);
            if(!dragon[i].isDying)
            {
                dragon[i].Move();
                dragon[i].Show(g_screen);
            }
            else
            {
                dragon[i].MoveDying();
                dragon[i].ShowDying(g_screen);
            }

            if(SDLCommonFunc::isKilled(p_player.GetRect(), dragon[i].GetRect()))
            {
                dragon[i].isDying = true;
            }
            else if(SDLCommonFunc::CheckCollision(dragon[i].GetRect(), p_player.GetRect()) && !dragon[i].isDying)
            {
                --hp_;
                if(hp_)
                {
                    dragon[i].isDeath = true;
                }
                else
                {
                    p_player.SetInput(0, 0);
                    hp_ = 3;
                    GameEndMenu(is_quit, false);
                    if(is_quit)
                    {
                        close();
                        return 0;
                    }
                    else
                    {
                        start_time = SDL_GetTicks()/1000;
                        p_player.SetPos(0, 0);
                        for(int i=0;i<5;i++) dragon[i].isDeath = true;
                        for(int i=0;i<10;i++) ball[i].moving = false;
                    }
                }
            }
        }

        /// Map
        game_map.SetMap(map_data);                              // Thay đổi lại map
        game_map.DrawMap(g_screen);                             // Load map ra mh  => map chạy theo nhân vật

        /// Show game's time
        string str_time = "Time: ";
        string str_val = to_string(int(SDL_GetTicks()/1000) - start_time);
        str_time += str_val;

        time_game.SetText(str_time);
        time_game.SetPos(SCREEN_WIDTH - 200, 15);
        time_game.LoadFromRenderText(font_time, g_screen);
        time_game.RenderText(g_screen);

        ///Show Player's HP
        string str_HP = "HP: " + to_string(hp_);

        HP_Players.SetText(str_HP);
        HP_Players.SetPos(50, 15);
        HP_Players.LoadFromRenderText(font_time, g_screen);
        HP_Players.RenderText(g_screen);


        SDL_RenderPresent(g_screen);

        /// Fix FPS
        deltaTime = fps_timer.get_ticks();

        if(deltaTime<time_one_frame)
        {
            int delay_time = time_one_frame - deltaTime;
            if(delay_time>=0)
                SDL_Delay(delay_time);
        }
        /// End
        time_game.Free();
        HP_Players.Free();
        p_player.Free();
        for(int i=0;i<10;i++) ball[i].Free();
        for(int i=0;i<5;i++) dragon[i].Free();
    }

    close();
    return 0;
}
