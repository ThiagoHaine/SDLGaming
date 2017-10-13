#include<stdio.h>
#include<stdlib.h>
#include"SDG.h"

int main(){
initSDG();
scene *room = initScene(640,480,640,480);
font *txt=newFont("font.ttf",48);
sprite *spr_block=new_sprite("sprites/block.png",1);
object *block=new_object("player",spr_block);
//block->gravity=0.1;
sceneElement *iBlock=instantiate(block,room,300,300);
camera *main_camera = newCamera(640,480,iBlock);
while(1){
  while(checkEvent(room)){
    if (sceneEvent(room).type==e_quit){
      return 1;
    }else if (sceneEvent(room).type==e_keydown){
      switch (sceneEvent(room).keyCheck) {
        case k_esc:
          return 1;
          break;
        case k_up:
          block->vspeed=-2;
          break;
        case k_left:
          block->hspeed=-2;
          block->vspeed=0;
          break;
        case k_right:
          block->hspeed=2;
          block->vspeed=0;
          break;
      }
    }else if (sceneEvent(room).type==e_keyup){
      if(sceneEvent(room).keyCheck==k_left || sceneEvent(room).keyCheck==k_right){
        block->hspeed=0;
      }
    }
    }
    drawText("Testando a escrita de textos",txt,room);
  drawScene(room,main_camera,"jogo de testes");
}
quitSDG();
return 1;
}
