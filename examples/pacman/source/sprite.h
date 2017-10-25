#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

sprite *newSprite(char *img_file,int spd);
void addSubimg(sprite *spr,char *img_file);
SDL_Surface *getImage(sceneElement *spr);
SDL_Surface *getSubimage(sprite *spr,int i);

sprite *newSprite(char *img_file,int spd){
  sprite *aux;
  subimg *subaux;
  aux=(sprite*)malloc(sizeof(sprite));
  subaux=(subimg*)malloc(sizeof(subimg));
  subaux->img=IMG_Load(img_file);
  subaux->prox=NULL;
  aux->size=1;
  aux->sub=1;
  aux->time=0;
  aux->speed=spd*10;
  aux->start=subaux;
  aux->last=subaux;
  return aux;
}

void addSubimg(sprite *spr,char *img_file){
  spr->size++;
  subimg *aux;
  subimg *new_sub;
  new_sub=(subimg*)malloc(sizeof(subimg));
  new_sub->img=IMG_Load(img_file);
  new_sub->prox=NULL;
  aux=spr->last;
  aux->prox=new_sub;
  spr->last=new_sub;
}

SDL_Surface *getImage(sceneElement *inst){
  #ifdef _WIN32
        int atual=0;
        subimg *aux;
        while(atual<inst->sub){
          if (atual==0){
            aux=inst->sprite_index->start;
          }else{
            aux=aux->prox;
          }
          atual++;
        }
        if (inst->clk==0){
          inst->clk=fps;
        }
        if (inst->sprite_index->size>1){
        if (inst->sprite_speed<=(inst->spr_time-inst->clk)){
          if (inst->sub<inst->sprite_index->size){
            inst->sub++;
          }else{
            inst->sub=1;
          }
          inst->clk=fps;
        }else{
          inst->spr_time=fps;
        }
          return aux->img;
        }else{
          return inst->sprite_index->start->img;
        }
  #else
        int atual=0;
        subimg *aux;
        while(atual<inst->sub){
          if (atual==0){
            aux=inst->sprite_index->start;
          }else{
            aux=aux->prox;
          }
          atual++;
        }
        if (inst->clk==0){
          inst->clk=(clock()/10000);
        }
        if (inst->sprite_index->size>1){
        if (inst->sprite_speed<=(inst->spr_time-inst->clk)){
          if (inst->sub<inst->sprite_index->size){
            inst->sub++;
          }else{
            inst->sub=1;
          }
          inst->clk=(clock()/10000);
        }else{
          inst->spr_time=(clock()/10000);
        }
          return aux->img;
        }else{
          return inst->sprite_index->start->img;
        }
  #endif
}

SDL_Surface *getSubimage(sprite *spr,int i){

  int atual=0;
  subimg *aux;
  while(atual<i){
    if (atual==0){
      aux=spr->start;
    }else{
      aux=aux->prox;
    }
    atual++;
  }
  return aux->img;
}
#endif // SPRITE_H_INCLUDED
