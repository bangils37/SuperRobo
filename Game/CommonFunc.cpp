
#include "CommonFunc.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect object1, const SDL_Rect object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w/8;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h/8;

    int left_b = object2.x;
    int right_b = object2.x + object2.w/8;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h/8;
//    cout<<'\n';
//    cout<<left_a<<' '<<right_a<<' '<<top_a<<' '<<bottom_a<<'\n';
//    cout<<left_b<<' '<<right_b<<' '<<top_b<<' '<<bottom_b<<'\n';

    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
//            cout<<1<<'\n';
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
//            cout<<1<<'\n';
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
//            cout<<3<<'\n';
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
//            cout<<4<<'\n';
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
//            cout<<5<<'\n';
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
//            cout<<6<<'\n';
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
//            cout<<7<<'\n';
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
//            cout<<8<<'\n';
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
//        cout<<9<<'\n';
        return true;
    }

    return false;
}

bool SDLCommonFunc::isKilled(const SDL_Rect killer_, const SDL_Rect victim_)
{
    int left_a = killer_.x;
    int right_a = killer_.x + killer_.w/8;
    int top_a = killer_.y;
    int bottom_a = killer_.y + killer_.h/8;

    int left_b = victim_.x;
    int right_b = victim_.x + victim_.w/8;
    int top_b = victim_.y;
    int bottom_b = victim_.y + victim_.h/8;

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}
