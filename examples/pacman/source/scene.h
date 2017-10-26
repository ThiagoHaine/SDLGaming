#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

void changeBackground(char * bg_file,bool fix,scene *scn);
scene *initScene(int width,int height,int window_width,int window_height);
camera *newCamera(int wview,int hview,sceneElement *act);
int checkEvent(scene *scn);
sceneElement *instantiate(object *obj,scene *scn,int x,int y);
sceneElement *instantiateImage(object *obj,scene *scn,int x,int y,int i);
void destroy(sceneElement *instance);
SDL_Event sceneEvent(scene *scn);
void drawScene(scene *scn,camera *cmr,char *name);

void changeBackground(char * bg_file,bool fix,scene *scn){
  scn->background=IMG_Load(bg_file);
  scn->fixed=fix;
}

scene *initScene(int width,int height,int window_width,int window_height){
  fps=30;
  scene *aux;
  aux=(scene*)malloc(sizeof(scene));
  aux->screen=SDL_SetVideoMode(window_width, window_height, 16, SDL_SWSURFACE);
  aux->video=SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  aux->background=NULL;
  aux->fixed=false;
  aux->init=NULL;
  aux->end=NULL;
  aux->idmax=0;
  aux->bufferSize=0;
  return aux;
}

camera *newCamera(int wview,int hview,sceneElement *act){
  camera *aux;
  aux=(camera*)malloc(sizeof(camera));
  aux->x=0;
  aux->y=0;
  aux->actor=act;
  aux->w=wview;
  aux->h=hview;
  return aux;
}

int checkEvent(scene *scn){
  return SDL_PollEvent(&scn->event);
}

bool instanceExists(char *name,scene *scn){
  sceneElement *aux;
  for(int i=0;i<scn->bufferSize;i++){
    if (i==0){
      aux=scn->init;
      if (aux->active==true && strcmp(aux->obj->name,name)==0){
        return true;
    }
    }else{
      aux=aux->next;
      if (aux->active==true && strcmp(aux->obj->name,name)==0){
        return true;
      }
    }
  }
  return false;
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
    aux->scn=scn;
    aux->clk=0;
    aux->img=-1;
    aux->y=y;
    aux->active=true;
    aux->prev=NULL;
    aux->next=NULL;
    aux->sub=obj->sprite_index->sub;
    aux->spr_time=0;
    aux->sprite_speed=obj->sprite_index->speed;

    aux->sprite_index=obj->sprite_index;
    aux->time[0]=0;
    aux->time[1]=0;
    aux->time[2]=0;
    aux->time[3]=0;
    aux->time[4]=0;
    aux->solid=obj->solid;
    aux->hspeed=obj->hspeed;
    aux->gravity=obj->gravity;
    aux->vspeed=obj->vspeed;

    scn->bufferSize++;
    return aux;
  }else{
    sceneElement *aux;
    aux=(sceneElement*)malloc(sizeof(sceneElement));
    aux->prev=scn->end;
    scn->end->next=aux;
    scn->end=aux;
    scn->idmax++;
    aux->img=-1;
    aux->active=true;
    aux->scn=scn;
    aux->obj=obj;
    aux->id=scn->idmax;
    aux->x=x;
    aux->y=y;
    aux->next=NULL;
    aux->clk=0;

    aux->sub=obj->sprite_index->sub;
    aux->spr_time=0;
    aux->sprite_speed=obj->sprite_index->speed;

    aux->sprite_index=obj->sprite_index;
    aux->time[0]=0;
    aux->time[1]=0;
    aux->time[2]=0;
    aux->time[3]=0;
    aux->time[4]=0;
    aux->solid=obj->solid;
    aux->hspeed=obj->hspeed;
    aux->gravity=obj->gravity;
    aux->vspeed=obj->vspeed;

    scn->bufferSize++;
    return aux;
  }
}

sceneElement *instantiateImage(object *obj,scene *scn,int x,int y,int i){
  if (scn->bufferSize==0){
    sceneElement *aux;
    aux=(sceneElement*)malloc(sizeof(sceneElement));
    scn->idmax++;
    scn->init=aux;
    scn->end=aux;
    aux->obj=obj;
    aux->id=scn->idmax;
    aux->x=x;
    aux->img=i;
    aux->scn=scn;

    aux->y=y;
    aux->active=true;
    aux->prev=NULL;
    aux->next=NULL;
    aux->clk=0;
    aux->sub=obj->sprite_index->sub;
    aux->spr_time=0;
    aux->sprite_speed=obj->sprite_index->speed;

    aux->sprite_index=obj->sprite_index;
    aux->time[0]=0;
    aux->time[1]=0;
    aux->time[2]=0;
    aux->time[3]=0;
    aux->time[4]=0;
    aux->solid=obj->solid;
    aux->hspeed=obj->hspeed;
    aux->gravity=obj->gravity;
    aux->vspeed=obj->vspeed;

    scn->bufferSize++;
    return aux;
  }else{
    sceneElement *aux;
    aux=(sceneElement*)malloc(sizeof(sceneElement));
    aux->prev=scn->end;
    scn->end->next=aux;
    scn->end=aux;
    scn->idmax++;
    aux->img=i;
    aux->scn=scn;
    aux->active=true;

    aux->obj=obj;
    aux->id=scn->idmax;
    aux->x=x;
    aux->y=y;
    aux->next=NULL;
    aux->clk=0;
    aux->sub=obj->sprite_index->sub;
    aux->spr_time=0;
    aux->sprite_speed=obj->sprite_index->speed;

    aux->sprite_index=obj->sprite_index;
    aux->time[0]=0;
    aux->time[1]=0;
    aux->time[2]=0;
    aux->time[3]=0;
    aux->time[4]=0;
    aux->solid=obj->solid;
    aux->hspeed=obj->hspeed;
    aux->gravity=obj->gravity;
    aux->vspeed=obj->vspeed;

    scn->bufferSize++;
    return aux;
  }
}

void destroy(sceneElement *instance){
    instance->active=false;
}

SDL_Event sceneEvent(scene *scn){
  return scn->event;
}

void drawScene(scene *scn,camera *cmr,char *name){
  SDL_WM_SetCaption(name, name);
  SDL_FillRect(scn->screen, NULL, 0x0);
  SDL_FillRect(scn->video, NULL, 0x0);
  if (cmr->actor!=NULL){
    cmr->x=cmr->actor->x-(cmr->w/2);
    cmr->y=cmr->actor->y-(cmr->h/2);
  }
  if (cmr->x<0){
    cmr->x=0;
  }
  if (cmr->y<0){
    cmr->y=0;
  }
  if ((cmr->x+cmr->w)>scn->video->w){
    cmr->x=scn->video->w-cmr->w;
  }
  if ((cmr->y+cmr->h)>scn->video->h){
    cmr->y=scn->video->h-cmr->h;
  }
  SDL_Rect auxrect = {cmr->x,cmr->y,(cmr->w+cmr->x),(cmr->h+cmr->y)};
  if (scn->background!=NULL){
    if (scn->fixed==false){
      SDL_BlitSurface(scn->background, NULL, scn->video, NULL);
    }else{
      SDL_BlitSurface(scn->background, NULL, scn->video, &auxrect);
    }
  }
  if (scn->bufferSize>0){
  sceneElement *aux;
  SDL_Rect posaux;
  for(int i=0;i<scn->bufferSize;i++){
    if (i==0){
      aux=scn->init;
      if (aux->active==true){
      step(aux);
      posaux.x=aux->x;
      posaux.y=aux->y;
      if (aux->sprite_index!=NULL){
      if (aux->img==-1){
      SDL_BlitSurface(getImage(aux), NULL, scn->video, &posaux);
    }else{
      SDL_BlitSurface(getSubimage(aux->sprite_index,aux->img), NULL, scn->video, &posaux);
    }
      }
      }
    }else{
      aux=aux->next;
      if (aux->active==true){
      step(aux);
      posaux.x=aux->x;
      posaux.y=aux->y;
      if (aux->sprite_index!=NULL){
      if (aux->img==-1){
      SDL_BlitSurface(getImage(aux), NULL, scn->video, &posaux);
    }else{
      SDL_BlitSurface(getSubimage(aux->sprite_index,aux->img), NULL, scn->video, &posaux);
    }
      }
      }
    }
  }
}
  SDL_BlitSurface(scn->video, &auxrect, scn->screen, NULL);
  SDL_UpdateRect(scn->screen, 0,0,0,0);
  SDL_Delay(1);
}

#endif // SCENE_H_INCLUDED
