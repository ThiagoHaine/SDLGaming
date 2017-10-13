#ifndef SDG_H_INCLUDED
#define SDG_H_INCLUDED

#include<string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "dict.h"
#include "sprite.h"
#include "object.h"
#include "scene.h"
#include "text.h"

void initSDG(){
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  int flags=IMG_INIT_JPG|IMG_INIT_PNG;
  int initted=IMG_Init(flags);
  if((initted&flags) != flags) {
      printf("IMG_Init: Failed to init required jpg and png support!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
  }
}

void quitSDG(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
}

#endif
