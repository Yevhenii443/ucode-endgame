#include "header.h"

#include <stdio.h>
int game_is_running = true;

void loadGame(GameState *game){
    SDL_Surface *Surface = NULL; 
    Surface = IMG_Load("resource/images/back/back.png");
    game->back = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);


    Surface = IMG_Load("resource/images/main_hero/death/fire.png");
    game->fire = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);

    Surface = IMG_Load("resource/images/main_hero/run/neo.png");
    game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);

    Surface = IMG_Load("resource/images/main_hero/run/neo2.png");
    game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);

    Surface = IMG_Load("resource/images/main_hero/run/neo3.png");
    game->manFrames[2] = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);

    Surface = IMG_Load("resource/images/main_hero/run/neo4.png");
    game->manFrames[3] = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);

    Surface = IMG_Load("resource/images/terrain/mud_block.png");
    game->brick = SDL_CreateTextureFromSurface(game->renderer, Surface);
    SDL_FreeSurface(Surface);
    
    game->man.x = 250;
    game->man.y = 144;
    game->man.dx = 0;
    game->man.dy = 0;
    game->man.onLedge = 0;
    game->man.animFrame = 0;
    game->time = 0;
    game->man.isDead = 0;
    game->forenter.enterornot = 1;
    game->man.facingLeft = 0;
    game->scrollX = 0;
    game->deathCountdown = -1;
   
    for(int i = 0;i < 100; i++)
    {
        game->fires[i].x = 320+random() % 38400;
        game->fires[i].y = random( ) % 600;
    }
    
    for(int i = 0; i < 100; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = i*256;
        if(i == 0)
            game->ledges[i].y = 400;
        else 
            game->ledges[i].y = 300+100-random()%200;
    }
    game->ledges[99].x = 350;
    game->ledges[99].y = 200;

    game->ledges[98].x = 350;
    game->ledges[98].y = 350;

}

void process(GameState *game)
{
    game->time++;
    
    if(!game->man.isDead)
    {

        Man *man = &game->man;
        man->x += man->dx;
        man->y += man->dy;
        if(man->dx != 0 && man->onLedge)
        {
            if(game->time % 8  == 0)
            {
                if(man->animFrame == 0)
                {
                    for(int i = 0; i < 4; i++)
                        man->animFrame = i;
                }
                else
                {
                    man->animFrame = 0; 
                } 
            }
        }
    man->dy += GRAVITY; 
        if(game->man.isDead && game->deathCountdown < 0)
        {
            game->deathCountdown = 120;
        }
        if(game->deathCountdown > 0)
        {
            game->deathCountdown--;
            if(game->deathCountdown < 0)
            {

            }
        }
    }



    game->scrollX = -game->man.x + 320;
    if(game->scrollX > 0)
        game->scrollX = 0;
}


int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}
void collisionDetect(GameState *game)
{
    for(int i = 0; i < 100; i++)
    {
        if(collide2d(game->man.x, game->man.y, game->fires[i].x, game->fires[i].y, 48, 48, 64, 64))
        {
            game->man.isDead = 1;
        }
    }

    for(int i = 0; i< 100; i++)
    {
        float mw = 48, mh = 48;
        float mx = game->man.x, my = game->man.y;
        float bx = game->ledges[i].x, by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h;

        if(mx+mw/2 > bx && mx+mw/2<bx+bw)
        {

            if(my < by+bh && my > by && game->man.dy < 0)
            {

                game->man.y = by+bh;
                my = by+bh;


                game->man.dy = 0;
                game->man.onLedge = 1;
            }
        if (mx+mw > bx && mx<bx+bw)
            {

                if(my+mh > by && my < by && game->man.dy > 0)
                {
                    game->man.y = by-mh;
                    my = by-mh;


                    game->man.dy = 0;
                    game->man.onLedge = 1;
                }
            }
        }
        if(my+mh > by && my<by+bh)
        {

            if(mx < bx+bw && mx+mw > bx+bw && game->man.dx < 0)
            {

                game->man.x = bx+bw;
                mx = bx+bw;
                game->man.dx = 0;
            }

            else if(mx+mw > bx && mx < bx && game->man.dx > 0)
            {

                game->man.x = bx-mw;
                mx = bx-mw;

                game->man.dx = 0;

            }
        }
    }
}


void processEvents(GameState *game){
    SDL_Event event;
    SDL_PollEvent(&event);
        switch(event.type) {
                case SDL_QUIT:
                    game_is_running = false;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        game_is_running = false;
                    }
                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        if(game->man.onLedge)
                            game->man.dy = -8;
                            game->man.onLedge = 0;
                    }

                break;
        }

    const Uint8 *state = SDL_GetKeyboardState(NULL); 
    if(state[SDL_SCANCODE_UP])
    {
        game->man.dy -= 0.2f;
    }



        if(state[SDL_SCANCODE_RIGHT])
        {
            game->man.dx += 10;
            if(game->man.dx > 6)
                game->man.dx = 6;
            game->man.facingLeft = 1;
        }
        else if(state[SDL_SCANCODE_LEFT])
        {
            game->man.dx -= 0.5;
            if(game->man.dx < -6)
                game->man.dx = -6;
            game->man.facingLeft = 0;
        }
        else
            game->man.animFrame = 0;
            game->man.dx *= 0.8f;
            if(fabsf(game->man.dx) < 0.1f)
                game->man.dx = 0;
               
}



void doRender(SDL_Renderer *renderer, GameState *game){
    SDL_RenderCopy(renderer, game->back, NULL, NULL);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 

    for(int i = 0;i < 100; i++)
    {
        SDL_Rect ledgeRect = {game->scrollX+game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);

    } 

    SDL_Rect rect = {game->scrollX+game->man.x, game->man.y, 70, 70};
    SDL_RenderCopyEx(renderer, game->manFrames[game->man.animFrame], NULL, &rect, 0, NULL, game->man.facingLeft == 0);
     
     if(game->man.isDead)
     {
        SDL_Rect rect = {game->scrollX+game->man.x-24+38/2+5, game->man.y-24-83/2, 38, 83};
        SDL_RenderCopyEx(renderer, game->fire, NULL, &rect, 0, NULL, game->time%20 < 10);
     }


    for(int i = 0; i < 100; i++)
    {
        SDL_Rect fireRect = {game->scrollX+game->fires[i].x, game->fires[i].y, 64, 64};
        SDL_RenderCopy(renderer, game->fire, NULL, &fireRect);
    }
    SDL_RenderPresent(renderer);
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    
    GameState gameState;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

  
    

    window = SDL_CreateWindow("Game window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gameState.renderer = renderer;
    
    int counter = 1;
    loadGame(&gameState);
    while(game_is_running == true) {
        while(counter != 0){

            counter = main_process(renderer, &gameState);
        }
        processEvents(&gameState);
        process(&gameState);
        collisionDetect(&gameState);
        doRender(renderer, &gameState);
    }


    SDL_DestroyTexture(gameState.manFrames[0]);
    SDL_DestroyTexture(gameState.manFrames[1]);
    SDL_DestroyTexture(gameState.manFrames[2]);
    SDL_DestroyTexture(gameState.manFrames[3]);
    SDL_DestroyTexture(gameState.brick);
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    


    return 0;

}

