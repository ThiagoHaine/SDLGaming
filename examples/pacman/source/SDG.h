#ifndef SDG_H_INCLUDED
#define SDG_H_INCLUDED

#include<string.h>
#include<time.h>
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

#ifdef _WIN32
ULONG lastTick=GetTickCount(),currTick=GetTickCount();
ULONG UPDATESPEED;
UINT frames=0;
float fps=60.0f;
float g_speed;

void CalcFPS()
{
  currTick=GetTickCount();
  ULONG tickDiff=currTick-lastTick;
  frames++;
  if(tickDiff>=UPDATESPEED)
    {
      lastTick=currTick;
      float calcVal=1/((float)UPDATESPEED/1000.0f);   // Inverse
      float fpsCalc=(float)frames*calcVal;        // Calculates our frames in one second
      fps+=fpsCalc;
      fps/=2;
      frames=0;
      g_speed=60/fps;
    }
}
#endif

void initSDG(){
  srand(time(NULL));
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
