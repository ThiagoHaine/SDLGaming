#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

typedef struct scene{
int idmax;
SDL_Surface * screen;
SDL_Event event;
int bufferSize;
struct sceneElement *init;
struct sceneElement *end;
}scene;

typedef struct sceneElement{
int id;
object *obj;
bool active;
int x;
int y;
struct sceneElement *prev;
struct sceneElement *next;
}sceneElement;

scene *initScene(int width,int height){
  SDL_Init(SDL_INIT_VIDEO);
  int flags=IMG_INIT_JPG|IMG_INIT_PNG;
  int initted=IMG_Init(flags);
  if((initted&flags) != flags) {
      printf("IMG_Init: Failed to init required jpg and png support!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
  }
  scene *aux;
  aux=(scene*)malloc(sizeof(scene));
  aux->screen=SDL_SetVideoMode(width, height, 16, SDL_SWSURFACE);
  aux->init=NULL;
  aux->end=NULL;
  aux->idmax=0;
  aux->bufferSize=0;
  return aux;
}

int checkEvent(scene *scn){
  return SDL_PollEvent(&scn->event);
}

sceneElement *instantiate(object *obj,scene *scn,int x,int y){
  if (scn->bufferSize==0){
    sceneElement *aux;
    aux=(sceneElement*)malloc(sizeof(sceneElement));
    scn->idmax++;
    scn->init=aux;
    scn->end=aux;
    aux->obj=obj;
    aux->id=scn->idmax;
    aux->x=x;
    aux->y=y;
    aux->active=true;
    aux->prev=NULL;
    aux->next=NULL;
    scn->bufferSize++;
    return aux;
  }else{
    sceneElement *aux;
    aux=(sceneElement*)malloc(sizeof(sceneElement));
    aux->prev=scn->end;
    scn->end->next=aux;
    scn->end=aux;
    scn->idmax++;
    aux->active=true;
    aux->obj=obj;
    aux->id=scn->idmax;
    aux->x=x;
    aux->y=y;
    aux->next=NULL;
    scn->bufferSize++;
    return aux;
  }
}

void destroy(sceneElement *instance,scene *scn){
    instance->active=false;
}

SDL_Event sceneEvent(scene *scn){
  return scn->event;
}

void drawScene(scene *scn){
  SDL_FillRect(scn->screen, NULL, 0x0);
  if (scn->bufferSize>0){
  sceneElement *aux;
  SDL_Rect posaux;
  for(int i=0;i<scn->bufferSize;i++){
    if (i==0){
      aux=scn->init;
      if (aux->active==true){
      step(aux->obj,aux->x,aux->y);
      posaux.x=aux->obj->x;
      posaux.y=aux->obj->y;
      SDL_BlitSurface(get_image(aux->obj->sprite_index), NULL, scn->screen, &posaux);
      }
    }else{
      aux=aux->next;
      if (aux->active==true){
      step(aux->obj,aux->x,aux->y);
      posaux.x=aux->obj->x;
      posaux.y=aux->obj->y;
      SDL_BlitSurface(get_image(aux->obj->sprite_index), NULL, scn->screen, &posaux);
      }
    }
  }
}
  SDL_UpdateRect(scn->screen, 0,0,0,0);
  SDL_Delay(1);
}

#endif // SCENE_H_INCLUDED
