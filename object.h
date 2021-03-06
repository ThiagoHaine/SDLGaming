#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

sceneElement *other;

object *newObject(char *name,sprite *spr);
void setSubimage(object *obj,int i);
void destroyObject(object *obj);
void step(sceneElement *inst);
bool collisionCheck(sceneElement *obj1,sceneElement *obj2);
bool collisionCheckPosition(sceneElement *obj2,int x,int y);
bool placeFree(sceneElement *obj,int x,int y);


object *newObject(char *name,sprite *spr){
  object *obj;
  obj=(object*)malloc(sizeof(object));
  obj->hspeed=0;
  obj->vspeed=0;
  obj->gravity=0;
  obj->solid=false;
  obj->time=0;
  obj->sprite_index=spr;
  strcpy(obj->name,name);
  return obj;
}

void setSubimage(object *obj,int i){
  obj->sprite_index->sub=i;
}

void destroyObject(object *obj){
  free(obj);
}

void step(sceneElement *inst){
  if (inst->gravity!=0){
    if (placeFree(inst,inst->x,inst->y+inst->vspeed+inst->gravity)){
    inst->vspeed+=inst->gravity;
    }
  }
  if (placeFree(inst,inst->x+inst->hspeed,inst->y)){
  inst->collisionSolid=false;
  inst->x+=inst->hspeed;
  }else{
    inst->collisionSolid=true;
    inst->hspeed=0;
  }
  if (placeFree(inst,inst->x,inst->y+inst->vspeed)){
  inst->y+=inst->vspeed;
  inst->collisionSolid=false;
  }else{
    inst->collisionSolid=true;
    inst->vspeed=0;
  }
}

bool collisionCheck(sceneElement *obj1,sceneElement *obj2){
  int x1,y1,w1,h1;
  int x2,y2,w2,h2;
  x1=obj1->x;
  y1=obj1->y;
  w1=getImage(obj1)->w;
  h1=getImage(obj1)->h;

  x2=obj2->x;
  y2=obj2->y;
  w2=getImage(obj2)->w;
  h2=getImage(obj2)->h;

  if ((x2>=x1 && x2<=(x1+w1)) && (y2>=y1 && y2<=(y1+h1))){
    return true;
  }else if (((x2+w2)>=x1 && (x2+w2)<=(x1+w1)) && (y2>=y1 && y2<=(y1+h1))){
    return true;
  }else if ((x2>=x1 && x2<=(x1+w1)) && ((y2+h2)>=y1 && (y2+h2)<=(y1+h1))){
    return true;
  }else if (((x2+w2)>=x1 && (x2+w2)<=(x1+w1)) && ((y2+h2)>=y1 && (y2+h2)<=(y1+h1))){
    return true;
  }else if ((x1>=x2 && x1<=(x2+w2)) && (y1>=y2 && y1<=(y2+h2))){
    return true;
  }else if (((x1+w1)>=x2 && (x1+w1)<=(x2+w2)) && (y1>=y2 && y1<=(y2+h2))){
    return true;
  }else if ((x1>=x2 && x1<=(x2+w2)) && ((y1+h1)>=y2 && (y1+h1)<=(y2+h2))){
    return true;
  }else if (((x1+w1)>=x2 && (x1+w1)<=(x2+w2)) && ((y1+h1)>=y2 && (y1+h1)<=(y2+h2))){
    return true;
  }else{
    return false;
  }
}

bool collisionCheckPosition(sceneElement *obj2,int x,int y){
  int x1,y1,w1,h1;
  int x2,y2,w2,h2;
  x1=x+1;
  y1=y+1;
  w1=getImage(obj2)->w-1;
  h1=getImage(obj2)->h-1;

  x2=obj2->x+1;
  y2=obj2->y+1;
  w2=getImage(obj2)->w-1;
  h2=getImage(obj2)->h-1;

  if ((x2>=x1 && x2<=(x1+w1)) && (y2>=y1 && y2<=(y1+h1))){
    return true;
  }else if (((x2+w2)>=x1 && (x2+w2)<=(x1+w1)) && (y2>=y1 && y2<=(y1+h1))){
    return true;
  }else if ((x2>=x1 && x2<=(x1+w1)) && ((y2+h2)>=y1 && (y2+h2)<=(y1+h1))){
    return true;
  }else if (((x2+w2)>=x1 && (x2+w2)<=(x1+w1)) && ((y2+h2)>=y1 && (y2+h2)<=(y1+h1))){
    return true;
  }else if ((x1>=x2 && x1<=(x2+w2)) && (y1>=y2 && y1<=(y2+h2))){
    return true;
  }else if (((x1+w1)>=x2 && (x1+w1)<=(x2+w2)) && (y1>=y2 && y1<=(y2+h2))){
    return true;
  }else if ((x1>=x2 && x1<=(x2+w2)) && ((y1+h1)>=y2 && (y1+h1)<=(y2+h2))){
    return true;
  }else if (((x1+w1)>=x2 && (x1+w1)<=(x2+w2)) && ((y1+h1)>=y2 && (y1+h1)<=(y2+h2))){
    return true;
  }else{
    return false;
  }
}

bool placeFree(sceneElement *obj,int x,int y){
  sceneElement *aux;
  for(int i=0;i<(obj->scn)->bufferSize;i++){
    if (i==0){
      aux=(obj->scn)->init;
      if (aux->active==true && aux->solid==true && aux->id!=obj->id){
        if (collisionCheckPosition(aux,x,y)){
          other=aux;
          return false;
        }
    }
    }else{
      aux=aux->next;
      if (aux->active==true && aux->solid==true && aux->id!=obj->id){
        if (collisionCheckPosition(aux,x,y)){
          other=aux;
          return false;
        }
      }
    }
  }
  return true;
}

sceneElement *collisionCheckName(sceneElement *obj,char *name){
  sceneElement *aux;
  for(int i=0;i<(obj->scn)->bufferSize;i++){
    if (i==0){
      aux=(obj->scn)->init;
      if (aux->active==true && aux->id!=obj->id && strcmp(aux->obj->name,name)==0){
        if (collisionCheck(obj,aux)){
          other=aux;
          return aux;
        }
    }
    }else{
      aux=aux->next;
      if (aux->active==true && aux->id!=obj->id && strcmp(aux->obj->name,name)==0){
        if (collisionCheck(obj,aux)){
          other=aux;
          return aux;
        }
      }
    }
  }
  return NULL;
}

bool wait(sceneElement *obj,int time,int n){
  if (obj->time[n]<=time){
    if (updateTime(obj,n)==1){
    obj->time[n]++;
    }
    return false;
  }else{
    obj->time[n]=0;
    return true;
  }
}
#endif // OBJECT_H_INCLUDED
