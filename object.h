#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

object *newObject(char *name,sprite *spr);
void setSubimage(object *obj,int i);
void destroyObject(object *obj);
void step(sceneElement *inst);
bool collisionCheck(sceneElement *obj1,sceneElement *obj2);
bool collisionCheckPosition(sceneElement *obj2,int x,int y);
bool placeFree(sceneElement *obj,int x,int y);
bool wait(object *obj,int time);

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
  if (inst->obj->gravity!=0){
    if (placeFree(inst,inst->x,inst->y+inst->obj->vspeed+inst->obj->gravity)){
    inst->obj->vspeed+=inst->obj->gravity;
    }
  }
  if (placeFree(inst,inst->x+inst->obj->hspeed,inst->y)){
  inst->x+=inst->obj->hspeed;
  }else{
    inst->obj->hspeed=0;
  }
  if (placeFree(inst,inst->x,inst->y+inst->obj->vspeed)){
  inst->y+=inst->obj->vspeed;
  }else{
    inst->obj->vspeed=0;
  }
}

bool collisionCheck(sceneElement *obj1,sceneElement *obj2){
  int x1,y1,w1,h1;
  int x2,y2,w2,h2;
  x1=obj1->x;
  y1=obj1->y;
  w1=getImage(obj1->obj->sprite_index)->w;
  h1=getImage(obj1->obj->sprite_index)->h;

  x2=obj2->x;
  y2=obj2->y;
  w2=getImage(obj2->obj->sprite_index)->w;
  h2=getImage(obj2->obj->sprite_index)->h;

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
  x1=x;
  y1=y;
  w1=getImage(obj2->obj->sprite_index)->w;
  h1=getImage(obj2->obj->sprite_index)->h;

  x2=obj2->x;
  y2=obj2->y;
  w2=getImage(obj2->obj->sprite_index)->w;
  h2=getImage(obj2->obj->sprite_index)->h;

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
      if (aux->active==true && aux->obj->solid==true){
        if (collisionCheckPosition(aux,x,y)){
          return false;
        }
    }
    }else{
      aux=aux->next;
      if (aux->active==true && aux->obj->solid==true){
        if (collisionCheckPosition(aux,x,y)){
          return false;
        }
      }
    }
  }
  return true;
}

bool wait(object *obj,int time){
  if (obj->time<time){
    obj->time++;
    return false;
  }else{
    obj->time=0;
    return true;
  }
}
#endif // OBJECT_H_INCLUDED
