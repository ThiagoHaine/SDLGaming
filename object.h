#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

object *new_object(char *name,sprite *spr){
  object *obj;
  obj=(object*)malloc(sizeof(object));
  obj->hspeed=0;
  obj->vspeed=0;
  obj->gravity=0;
  obj->time=0;
  obj->sprite_index=spr;
  strcpy(obj->name,name);
  return obj;
}

void setSubimage(object *obj,int i){
  obj->sprite_index->sub=i;
}

void destroy_object(object *obj){
  free(obj);
}

void step(sceneElement *inst){
  if (inst->obj->gravity!=0){
    inst->obj->vspeed+=inst->obj->gravity;
  }
  inst->x+=inst->obj->hspeed;
  inst->y+=inst->obj->vspeed;
}

bool collision_check(sceneElement *obj1,sceneElement *obj2){
  int x1,y1,w1,h1;
  int x2,y2,w2,h2;
  x1=obj1->x;
  y1=obj1->y;
  w1=get_image(obj1->obj->sprite_index)->w;
  h1=get_image(obj1->obj->sprite_index)->h;

  x2=obj2->x;
  y2=obj2->y;
  w2=get_image(obj2->obj->sprite_index)->w;
  h2=get_image(obj2->obj->sprite_index)->h;

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
