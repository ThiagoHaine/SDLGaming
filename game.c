#include<stdio.h>
#include<stdlib.h>
#include"SDG.h"

void room1();

int main(){
initSDG();
room1();
quitSDG();
return 1;
}

void room1(){
  scene *room=initScene(640,480,640,480);
  camera *cmr=newCamera(640,480,NULL);
  int menu=0,go=1;
  font *fnt_logo=newFont("font.ttf",48);
  font *fnt_menu=newFont("font.ttf",16);
  sprite *spr_logo=newText("Exemplo",fnt_logo);
  sprite *spr_menu=newText("-----Menu-----",fnt_menu);
  addTextSequence(spr_menu,"Start",fnt_menu,1);
  addTextSequence(spr_menu,"Config",fnt_menu,1);
  addTextSequence(spr_menu,"Exit",fnt_menu,1);
  addTextSequence(spr_menu,">",fnt_menu,1);
  object *obj_logo=new_object("Logo",spr_logo);
  object *obj_menu=new_object("Menu",spr_menu);
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
        if (menu==2){
        go=0;
        }
      }
    }
    selector->y=320+(20*menu);
  drawScene(room,cmr,"Room1");
  }
}
