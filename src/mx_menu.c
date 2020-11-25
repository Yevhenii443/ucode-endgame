#include "header.h"

bool main_process(SDL_Renderer *ren, GameState *game) {

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  bool run = true;  
  int i = 0;
  

  SDL_Event event;
  SDL_Rect start;
  SDL_Rect matrix;
  SDL_Rect neo;

  SDL_Texture *tex[19];
  SDL_Texture *start_button;
  SDL_Texture *matrix_logo;
  start_button = IMG_LoadTexture(ren, "resources2/start.png");
  matrix_logo = IMG_LoadTexture(ren, "resources2/matrix.png");


  start.x = (1200 / 2) - 250;
  start.y = 400;
  start.w = 500;
  start.h = 120;

  neo.x = 100;
  neo.y = 100;
  neo.w = 100;
  neo.h = 100;

  matrix.x = (1200 / 2) - 450;
  matrix.y = 100;
  matrix.w = 900;
  matrix.h = 100;

  tex[0] = IMG_LoadTexture(ren, "resources2/0.png");
  tex[1] = IMG_LoadTexture(ren, "resources2/1.png");
  tex[2] = IMG_LoadTexture(ren, "resources2/2.png");
  tex[3] = IMG_LoadTexture(ren, "resources2/3.png");
  tex[4] = IMG_LoadTexture(ren, "resources2/4.png");
  tex[5] = IMG_LoadTexture(ren, "resources2/5.png");
  tex[6] = IMG_LoadTexture(ren, "resources2/6.png");
  tex[7] = IMG_LoadTexture(ren, "resources2/7.png");
  tex[8] = IMG_LoadTexture(ren, "resources2/8.png");
  tex[9] = IMG_LoadTexture(ren, "resources2/9.png");
  tex[10] = IMG_LoadTexture(ren, "resources2/10.png");
  tex[11] = IMG_LoadTexture(ren, "resources2/11.png");
  tex[12] = IMG_LoadTexture(ren, "resources2/12.png");
  tex[13] = IMG_LoadTexture(ren, "resources2/13.png");
  tex[14] = IMG_LoadTexture(ren, "resources2/14.png");
  tex[15] = IMG_LoadTexture(ren, "resources2/15.png");
  tex[16] = IMG_LoadTexture(ren, "resources2/16.png");
  tex[17] = IMG_LoadTexture(ren, "resources2/17.png");
  tex[18] = IMG_LoadTexture(ren, "resources2/18.png");


  while(run == true) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          run = false;
          break;
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_RETURN) {
            printf("The i in func%d\n", game->forenter.enterornot);
            return 0;
            break;
          }
      }
    }
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex[i], NULL, NULL);
    SDL_RenderCopy(ren, start_button, NULL, &start);
    SDL_RenderCopy(ren, matrix_logo, NULL, &matrix);
    SDL_RenderPresent(ren);
    i++;
    if(i == 19) {
      i = 0;
    }
  }
  SDL_DestroyRenderer(ren);
  return true;

}

// int main() {
//   main_process();
// }
