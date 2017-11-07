#ifndef SDG_H_INCLUDED
#define SDG_H_INCLUDED

#include<string.h>
#include<time.h>
#include<stdint.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "dict.h"
#include "sound.h"
#include "sprite.h"
#include "object.h"
#include "scene.h"
#include "text.h"

void initSDG();
void quitSDG();


void initSDG(){
  srand(time(NULL));
  fps_now=time(0);
  fps_tm = localtime(&fps_now);
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  int flags=IMG_INIT_JPG|IMG_INIT_PNG;
  int initted=IMG_Init(flags);
  if((initted&flags) != flags) {
      printf("IMG_Init: Failed to init required jpg and png support!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
  }
  Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
}

void quitSDG(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
}
    

int randomize(int n){
return rand() % n;
}

#endif
