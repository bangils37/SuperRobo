
#ifndef FIRE_BALL_H
#define FIRE_BALL_H

#include "CommonFunc.h"
#include "BaseObject.h"


#define BALL_SPEED 10

class FireBall : public BaseObject
{
public:
    FireBall();
    ~FireBall();

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();
    void Move();
    void Free();

    void SetPos(const int& x, const int& y) {x_pos_ = x; y_pos_ = y;};
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    SDL_Rect GetRect() const {return rect_;};

    bool moving;

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    int frame_;

    int map_x_;
    int map_y_;
};

#endif // FIRE_BALL_H

