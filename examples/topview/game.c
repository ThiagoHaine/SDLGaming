#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "lib/sprite.h"
#include "lib/object.h"
#include "lib/scene.h"

int main(){
scene *room = initScene(640,480);
sprite *spr_block=new_sprite("sprites/block.png",1);
object *block=new_object("player",spr_block);
instantiate(block,room,300,300);
while(1){
  drawScene(room);
}
SDL_Quit();
return 1;
}
