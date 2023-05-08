
#ifndef DRAGON_OBJECT_H
#define DRAGON_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"


#define DRAGON_SPEED 5
#define DRAGON_FALLING 30

class DragonObject : public BaseObject
{
public:
    DragonObject();
    ~DragonObject();

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();
    void Move();
    void ShowDying(SDL_Renderer* des);
    void MoveDying();

    void SetPos(const int& x, const int& y) {x_pos_ = x; y_pos_ = y;};
    void SetTarget(const int &x, const int& y) {x_target_ = x; y_target_ = y;};
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    void GetPos(int &x, int &y) {x = x_pos_; y = y_pos_;};
    SDL_Rect GetRect() const {return rect_;};
    void Free();

    bool isDeath;
    bool isDying;

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

    float x_target_;
    float y_target_;
};

#endif // DRAGON_OBJECT_H

