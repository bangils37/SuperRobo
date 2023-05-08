
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

/// Screen
const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define TILE_SIZE 64

#define MAX_MAP_X 84
#define MAX_MAP_Y 10


typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect object1, const SDL_Rect object2);
    bool isKilled(const SDL_Rect killer_, const SDL_Rect victim_);
}

#endif // COMMON_FUNCTION_H_
