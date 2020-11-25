#pragma once

//our frameworks
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>


//system libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

typedef struct{
    SDL_Window *window;
    // SDL_Renderer *renderer;
}winrer;

typedef struct 
{
    float x, y;
    float dy, dx;
    short life;
    char *name;
    int onLedge, isDead;

    int animFrame, facingLeft;
}Man;

typedef struct
{
    int x, y, w, h;
} Ledge;


typedef struct 
{
    int x, y;
}Fire;

typedef struct
{
    int enterornot;
}forenter;

typedef struct
{
    forenter forenter;
    float scrollX;
    ///Players
    Man man;
    //fires
    Fire fires [100]; 
    //Ledges
    Ledge ledges[100];
    //images
    SDL_Texture *fire;
    SDL_Texture *manFrames[4];
    SDL_Texture *brick;
    SDL_Texture *back;

    int time, deathCountdown;
    //renderer
    SDL_Renderer *renderer;
    //window

}GameState;
 


#define FALSE 0
#define TRUE 1
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define GRAVITY 0.35f
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
//int processEvents(SDL_Window *window, GameState *game);
//void doRender(SDL_Renderer *renderer, GameState *game);
//void loadGame(GameState *game);

bool main_process(SDL_Renderer *ren, GameState *game);




// typedef struct
// {
//     int x, y;
//     short life;
//     char *name;
// } Man;


// typedef struct 
// {
//     int x, y;
// } Star;

// typedef struct 
// {
//     int x, y, w, h;
// } Ledge;


// typedef struct 
// {
//     Man man;

//     Star stars[100];
//     Ledge ledges[100];

//     SDL_Texture *star;
//     SDL_Texture *manFrames[2];
//     SDL_Texture *brick;

//     SDL_Renderer *renderer;

// } GameState;





///collision

//    for(int i = 0; i< 100; i++)
//     {
//         float mw = 48, mh = 48;
//         float mx = game->man.x, my = game->man.y;
//         float bx = game->ledges[i].x, by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h;

//         if(my+mh > by && my<by+bh)
//         {
//             ///rubbing against right edge
//             if(mx < bx+bw && mx+mw >= bx+bw)
//             {
//                 //correct x
//                 game->man.x = bx+bw;
//                 mx = bx+bw;
//             }
//             //rubbing against left edge
//             else if (mx+mw >= bx && mx < bx)
//             {
//                 // correct x
//                 game->man.x = bx-mw;
//                 mx = bx-mw;
//             }
//         }
//         if(mx+mw > bx && mx<bx+bw)
//         {
//             //are we bumping our head
//             if(my < by+bh && my > by)
//             {
//                 //correct y
//                 game->man.y = by+bh;
//                 //bumped our head stop any jump velocity
//                 game->man.dy = 0;
//                 game->man.onLedge = 1;
//             }
//             //are we landing on the ledje
//             else if(my+mh > by && my < by)
//             {
//                 // correct y
//                 game->man.y = by-mh;

//                 //landed on this ledge, stop any velocity
//                 game->man.dy = 0;
//                 game->man.onLedge = 1;
//             }
//         }

