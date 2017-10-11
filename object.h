#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

typedef enum { false, true } bool;

typedef struct object{
SDL_Rect pos;
int x;
int time;
int y;
float hspeed;
float gravity;
sprite *sprite_index;
float vspeed;
char name[10];
}object;

object *new_object(char *name,sprite *spr){
  object *obj;
  obj=(object*)malloc(sizeof(object));
  obj->hspeed=0;
  obj->vspeed=0;
  obj->gravity=0;
  obj->time=0;
  obj->sprite_index=spr;
  strcpy(obj->name,name);
  obj->pos.x=0;
  obj->pos.y=0;
  return obj;
}

void step(object *obj,int x,int y){
  if (obj->gravity!=0){
    obj->vspeed+=obj->gravity;
  }
  obj->pos.x+=obj->hspeed;
  obj->pos.y+=obj->vspeed;
  x+=obj->pos.x;
  obj->x=x;
  y+=obj->pos.y;
  obj->y=y;
  SDL_Rect aux;
  aux.x=x;
  aux.y=y;
}

bool collision_check(object *obj1,object *obj2){
  int x1,y1,w1,h1;
  int x2,y2,w2,h2;
  x1=obj1->x;
  y1=obj1->y;
  w1=get_image(obj1->sprite_index)->w;
  h1=get_image(obj1->sprite_index)->h;

  x2=obj2->x;
  y2=obj2->y;
  w2=get_image(obj2->sprite_index)->w;
  h2=get_image(obj2->sprite_index)->h;

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
