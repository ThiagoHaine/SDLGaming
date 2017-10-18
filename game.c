#include<stdio.h>
#include<stdlib.h>
#include"SDG.h"

int room1();
int room2();

int main(){
initSDG();
switch(room1()){
  case 0:
    room2();
    break;
}
quitSDG();
return 1;
}

int room1(){
  scene *room=initScene(640,480,640,480);
  camera *cmr=newCamera(640,480,NULL);
  int menu=0,go=1;
  font *fnt_logo=newFont("font.ttf",48);
  font *fnt_menu=newFont("font.ttf",16);
  sprite *spr_logo=newText("Exemplo",fnt_logo,c_white);
  sprite *spr_menu=newText("-----Menu-----",fnt_menu,c_white);
  addTextSequence(spr_menu,"Start",fnt_menu,1,c_dkorange);
  addTextSequence(spr_menu,"Config",fnt_menu,1,c_blue);
  addTextSequence(spr_menu,"Exit",fnt_menu,1,c_yellow);
  addTextSequence(spr_menu,">",fnt_menu,1,c_gray);
  object *obj_logo=newObject("Logo",spr_logo);
  object *obj_menu=newObject("Menu",spr_menu);
  instantiate(obj_logo,room,200,100);
  instantiateImage(obj_menu,room,250,300,1);
  instantiateImage(obj_menu,room,250,320,2);
  instantiateImage(obj_menu,room,250,340,3);
  instantiateImage(obj_menu,room,250,360,4);
  sceneElement *selector=instantiateImage(obj_menu,room,230,320+(20*menu),5);
  while(go==1){
    while(checkEvent(room)){
      if (sceneEvent(room).type==e_keyup){
        if (sceneEvent(room).keyCheck==k_down){
          if (menu<2){
            menu++;
          }else{
            menu=0;
          }
        }
      }else if (sceneEvent(room).keyCheck==k_up){
        if (menu>0){
          menu--;
        }else{
          menu=2;
        }
      }else if (sceneEvent(room).keyCheck==k_enter){
          return menu;
      }
    }
    selector->y=320+(20*menu);
  drawScene(room,cmr,"Room1");
  }
}

int room2(){
  scene *room=initScene(700,500,700,500);
  camera *cmr=newCamera(700,500,NULL);
  bool left=false,right=false;
  sprite *spr_player=newSprite("sprites/block.png",1);
  object *obj_player=newObject("Player",spr_player);
  object *obj_block=newObject("Block",spr_player);
  obj_block->solid=true;
  obj_player->gravity=0.1;
  sceneElement *player = instantiate(obj_player,room,100,0);
  instantiate(obj_block,room,288,100);
  instantiate(obj_block,room,0,100);
  for(int i=0;i<10;i++){
  instantiate(obj_block,room,0+(i*32),468);
  }
  while(1){
    while(checkEvent(room)){
      if (sceneEvent(room).type==e_keydown){
        if (sceneEvent(room).keyCheck==k_esc){
          return 1;
        }
        if (sceneEvent(room).keyCheck==k_left){
          left=true;
        }
        if (sceneEvent(room).keyCheck==k_right){
          right=true;
        }
        if (sceneEvent(room).keyCheck==k_up){
          player->vspeed=-2;
        }
      }
      if (sceneEvent(room).type==e_keyup){
        if (sceneEvent(room).keyCheck==k_left){
          left=false;
        }
        if (sceneEvent(room).keyCheck==k_right){
          right=false;
        }
      }
    }
  if (left){
    player->hspeed=-2;
  }else if (right){
    player->hspeed=2;
  }else{
    player->hspeed=0;
  }
  drawScene(room,cmr,"Room2");
  }
}
