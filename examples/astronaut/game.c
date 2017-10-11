#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "sprite.h"
#include "object.h"
#include "scene.h"


int main(){
  scene *room = initScene(640,480);
  changeBackground("wallpaper.png",room);
  //player
  //VARS
  bool playerInGround=false;
  int playerJump=0;
  int playerShot=0;
  int playerMove=0;
  int playerSide=1;
  //SPRITES
  sprite *player_idle_right=new_sprite("sprites/right/stand.png",1);
  sprite *player_walk_right=new_sprite("sprites/right/1.png",150);
  sprite *player_idle_left=new_sprite("sprites/left/stand.png",1);
  sprite *player_walk_left=new_sprite("sprites/left/1.png",150);
  sprite *player_shot_left=new_sprite("sprites/left/shot.png",1);
  sprite *player_shot_right=new_sprite("sprites/right/shot.png",1);
  sprite *spr_shot=new_sprite("sprites/shot.png",1);
  add_subimg(player_walk_right,"sprites/right/2.png");
  add_subimg(player_walk_left,"sprites/left/2.png");
  //CRIA O OBJETO
  object *player=new_object("player",player_idle_right);
  player->gravity=0.05;
  object *shot;
  sceneElement *iShot;

  //chao
  //SPRITE
  sprite *spr_block=new_sprite("block.png",1);
  //OBJETO
  object *block[40];
  sceneElement *iBlock[40];
  for(int i=0;i<40;i++){
  block[i]=new_object("block",spr_block);
  }
  sceneElement *iPlayer=instantiate(player,room,30,30);
  for(int i=0;i<20;i++){
  iBlock[i]=instantiate(block[i],room,0+(32*i),448);
  }
  for(int i=0;i<10;i++){
  iBlock[i+20]=instantiate(block[i+20],room,0+(32*i),250);
  }  
  while(1){
  if (playerInGround==false){
    player->gravity=0.05;
  }else{
    player->gravity=0;
  }
  while(checkEvent(room)){
    if (sceneEvent(room).type==SDL_QUIT){
      return 1;
    }
    if (sceneEvent(room).type==SDL_KEYDOWN){
      if (playerShot==0){
      if (sceneEvent(room).key.keysym.sym==SDLK_LEFT){
        playerSide=0;
        player->hspeed=-1;
      }
      if (sceneEvent(room).key.keysym.sym==SDLK_RIGHT){
        playerSide=1;
        player->hspeed=1;
      }}
      if (sceneEvent(room).key.keysym.sym==SDLK_UP){
        if (playerJump==0 && playerShot==0){
        player->y-=100;
        player->vspeed=-4;
        if (playerInGround==true){
          playerInGround=false;
        }
        playerJump=1;
        }
      }
      if (sceneEvent(room).key.keysym.sym==SDLK_z){
        if (playerShot==0){
        shot=new_object("shot",spr_shot);
        iShot=instantiate(shot,room,player->x+15,player->y+35);
        switch (playerSide) {
          case 1:
            shot->hspeed=8;
            break;
          case 0:
            shot->hspeed=-8;
            break;
        }
        playerShot=1;
        }
      }
    }
    if (sceneEvent(room).type==SDL_KEYUP){
      if (sceneEvent(room).key.keysym.sym==SDLK_LEFT && player->hspeed<0){
        player->hspeed=0;
      }
      if (sceneEvent(room).key.keysym.sym==SDLK_RIGHT && player->hspeed>0){
        player->hspeed=0;
      }
    }
  }
  if (playerShot==1){
    if (wait(player,20)==true){
      destroy(iShot,room);
      destroy_object(shot);
      playerShot=0;
    }
    player->hspeed=0;
    switch (playerSide) {
      case 1:
        player->sprite_index=player_shot_right;
        break;
      case 0:
        player->sprite_index=player_shot_left;
        break;
    }
  }else{
  if (player->hspeed!=0){
    playerMove=1;
    switch (playerSide) {
      case 1:
        player->sprite_index=player_walk_right;
        break;
      case 0:
        player->sprite_index=player_walk_left;
        break;
    }
  }else{
    playerMove=0;
    switch (playerSide) {
      case 1:
        player->sprite_index=player_idle_right;
        break;
      case 0:
        player->sprite_index=player_idle_left;
        break;
    }
  }
  }


  for(int i=0;i<30;i++){
    if (collision_check(player,block[i])==true){
      if (block[i]->y<player->y){
        player->vspeed=1;
      }else{
      if(playerInGround==false){
        player->vspeed=0;
        playerJump=0;
      }
      playerInGround=true;}
    }else{
      playerInGround=false;
    }
  }



  drawScene(room);
  }
  SDL_Quit();
  return 1;
}
