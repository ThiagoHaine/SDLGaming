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
  music *msc_opening=addMusic("music/opening.mp3");
  musicPlay(msc_opening,0);
  scene *room=initScene(640,480,640,480);
  camera *cmr=newCamera(640,480,NULL);
  int menu=0,go=1;
  font *fnt_logo=newFont("font.ttf",48);
  font *fnt_menu=newFont("font.ttf",16);
  sprite *spr_logo=newText("Pacman",fnt_logo,c_white);
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
    calcFPS();
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
          musicStop();
          return menu;
      }
    }
    selector->y=320+(20*menu);
  drawScene(room,cmr,"Room1");
  }
}

int room2(){
  font *fnt_pts=newFont("font.ttf",16);
  sound *snd_normal=addSound("music/chomp.wav");
  music *msc_normal=addMusic("music/nochomp.wav");
  music *msc_ghost=addMusic("music/phantom.wav");
  sound *snd_cherry=addSound("music/cherry.wav");
  sound *snd_ghost=addSound("music/chomp-g.wav");
  sound *snd_die=addSound("music/die.wav");
  char pts[4];
  scene *room=initScene(672,512,672,512);
  camera *cmr=newCamera(672,512,NULL);
  bool left=false,right=false,up=false,down=false;
  sprite *spr_player=newSprite("sprites/block.png",1);
  int points=0;
  sprintf(pts,"%d",points);
  bool die=false;
  sprite *txt_points=newText(pts,fnt_pts,c_black);
  object *obj_pts=newObject("pts",txt_points);
  sprite *spr_fruit=newSprite("pacman/fruit.png",1);
  object *obj_fruit=newObject("fruit",spr_fruit);
  sprite *spr_right=newSprite("pacman/1.png",5);
  addSubimg(spr_right,"pacman/2.png");
  sprite *spr_left=newSprite("pacman/5.png",5);
  addSubimg(spr_left,"pacman/2.png");
  sprite *spr_up=newSprite("pacman/3.png",5);
  addSubimg(spr_up,"pacman/2.png");
  sprite *spr_down=newSprite("pacman/7.png",5);
  addSubimg(spr_down,"pacman/2.png");
  sprite *spr_point=newSprite("pacman/point.png",1);
  object *obj_player=newObject("Player",spr_right);
  object *obj_block=newObject("Block",spr_player);
  object *obj_point=newObject("Point",spr_point);
  obj_block->solid=true;
  //FANTASMA
  sprite *spr_pright=newSprite("pacman/phantom/1.png",1);
  sprite *spr_pleft=newSprite("pacman/phantom/2.png",1);
  sprite *spr_pdown=newSprite("pacman/phantom/3.png",1);
  sprite *spr_pup=newSprite("pacman/phantom/4.png",1);
  sprite *spr_pblue=newSprite("pacman/phantom/blue.png",1);
  object *obj_phantom=newObject("phantom",spr_pright);
  sceneElement *phantom[5];
  bool blue=false;
  int act[5];
  for(int i=0;i<5;i++){
    phantom[i]=instantiate(obj_phantom,room,256+(32*i),288);
  }
  musicPlay(msc_normal,-1);
  sceneElement *player = instantiate(obj_player,room,32,32);

  for(int i=0;i<20;i++){
  instantiate(obj_block,room,0+(i*32),480);
  }
  for(int i=0;i<21;i++){
  instantiate(obj_block,room,0+(i*32),0);
  }
  for(int i=0;i<8;i++){
  instantiate(obj_block,room,64+(i*32),64);
  }
  for(int i=0;i<8;i++){
  instantiate(obj_block,room,352+(i*32),416);
  }
  for(int i=0;i<8;i++){
  instantiate(obj_block,room,64+(i*32),416);
  }
  for(int i=0;i<8;i++){
  instantiate(obj_block,room,352+(i*32),64);
  }
  for(int i=0;i<4;i++){
  instantiate(obj_block,room,64,96+(i*32));
  }
  for(int i=0;i<4;i++){
  instantiate(obj_block,room,64,288+(i*32));
  }
  for(int i=0;i<4;i++){
  instantiate(obj_block,room,576,96+(i*32));
  }
  for(int i=0;i<4;i++){
  instantiate(obj_block,room,576,288+(i*32));
  }

  for(int i=0;i<6;i++){
  instantiate(obj_block,room,128+(i*32),128);
  }
  for(int i=0;i<6;i++){
  instantiate(obj_block,room,352+(i*32),128);
  }
  for(int i=0;i<6;i++){
  instantiate(obj_block,room,128+(i*32),224);
  }
  for(int i=0;i<6;i++){
  instantiate(obj_block,room,352+(i*32),224);
  }

  for(int i=0;i<2;i++){
  instantiate(obj_block,room,128,160+(i*32));
  }
  for(int i=0;i<2;i++){
  instantiate(obj_block,room,512,160+(i*32));
  }

  for(int i=0;i<4;i++){
  instantiate(obj_block,room,224,256+(i*32));
  }
  for(int i=0;i<4;i++){
  instantiate(obj_block,room,416,256+(i*32));
  }

  for(int i=0;i<2;i++){
  instantiate(obj_block,room,256+(i*32),352);
  }
  for(int i=0;i<2;i++){
  instantiate(obj_block,room,384-(i*32),352);
  }


  for(int i=0;i<14;i++){
  if (i!=6 && i!=7){
  instantiate(obj_block,room,0,32+(i*32));
  }
  }
  for(int i=0;i<15;i++){
  if (i!=6 && i!=7){
  instantiate(obj_block,room,640,32+(i*32));
  }
  }
  for(int i=0;i<16;i++){
    for (int j=0;j<21;j++){
      if (placeFree(player,(32*j),(32*i))){
      instantiate(obj_point,room,8+(32*j),8+(32*i));
      }
    }
  }
  instantiate(obj_pts,room,10,10);
  while(1){
    calcFPS();
    sprintf(pts,"%d",fps);
    updateText(txt_points,pts,fnt_pts,c_black);
      Mix_VolumeMusic(MIX_MAX_VOLUME/5);
  Mix_Volume(-1,MIX_MAX_VOLUME/3);
    while(checkEvent(room)){
      if (sceneEvent(room).type==e_keydown){
        if (sceneEvent(room).keyCheck==k_esc){
          return 1;
        }
        if (sceneEvent(room).keyCheck==k_left){
          left=true;
          right=false;
          up=false;
          down=false;
        }
        if (sceneEvent(room).keyCheck==k_right){
          right=true;
          left=false;
          up=false;
          down=false;
        }
        if (sceneEvent(room).keyCheck==k_up){
          up=true;
          down=false;
          left=false;
          right=false;
        }
        if (sceneEvent(room).keyCheck==k_down){
          down=true;
          up=false;
          left=false;
          right=false;
        }
      }
    }
  if (!instanceExists("fruit",room)){
  if (wait(player,5,0)){
    instantiate(obj_fruit,room,320,192);
  }
  }
  for(int i=0;i<5;i++){
    if (wait(phantom[i],1,0)){
      act[i]=randomize(4)+1;
    }
    if (phantom[i]->hspeed==0 && phantom[i]->vspeed==0){
      act[i]=randomize(4)+1;
    }
    if (collisionCheckName(phantom[i],"phantom")){
      act[i]=randomize(4)+1;
    }
    if ((phantom[i]->x%32)==0 && (phantom[i]->y%32)==0 && act[i]!=5){
          if (act[i]==1){
            phantom[i]->hspeed=-2;
            phantom[i]->vspeed=0;
          }
          if (act[i]==2){
            phantom[i]->hspeed=2;
            phantom[i]->vspeed=0;
          }
          if (act[i]==3){
            phantom[i]->hspeed=0;
            phantom[i]->vspeed=-2;
          }
          if (act[i]==4){
            phantom[i]->hspeed=0;
            phantom[i]->vspeed=2;
          }
    }
    if (blue==false){
    if (phantom[i]->hspeed<0){
      phantom[i]->sprite_index=spr_pleft;
    }else if (phantom[i]->hspeed>0){
      phantom[i]->sprite_index=spr_pright;
    }else if (phantom[i]->vspeed>0){
      phantom[i]->sprite_index=spr_pdown;
    }else{
      phantom[i]->sprite_index=spr_pup;
    }}else{
      if (phantom[i]->sprite_index!=spr_pblue){
      phantom[i]->sprite_index=spr_pblue;  
      phantom[i]->time[1]=0;
    }
      if (wait(phantom[i],10,1)){
        blue=false;
        musicPlay(msc_normal,-1);
      }
    }

    if (phantom[i]->x<-32 && phantom[i]->hspeed<0){
      phantom[i]->x=672;
    }
    if (phantom[i]->x>672 && phantom[i]->hspeed>0){
      phantom[i]->x=-32;
    }
  }
  if ((player->x%32)==0 && (player->y%32)==0){
    if (left && placeFree(player,player->x-2,player->y)){
      player->vspeed=0;
      player->hspeed=-2;
      player->sprite_index=spr_left;
      left=false;
    }
    if (right && placeFree(player,player->x+2,player->y)){
      player->vspeed=0;
      player->hspeed=2;
      player->sprite_index=spr_right;
      right=false;
    }
    if (up && placeFree(player,player->x,player->y-2) && player->x>0 && player->x<672){
      player->vspeed=-2;
      player->hspeed=0;
      player->sprite_index=spr_up;
      up=false;
    }
    if (down && placeFree(player,player->x,player->y+2) && player->x>0 && player->x<672){
      player->vspeed=2;
      player->hspeed=0;
      player->sprite_index=spr_down;
      down=false;
    }
  }
  if (player->x<-32 && player->hspeed<0){
    player->x=672;
  }
  if (player->x>672 && player->hspeed>0){
    player->x=-32;
  }

  if (collisionCheckName(player,"Point")!=NULL){
    if (!soundIsPlaying(snd_normal)){
      soundPlay(snd_normal);
    }
    destroy(other);
    points+=10;
    //sprintf(pts,"%d",points);
    sprintf(pts,"%d",fps);
    updateText(txt_points,pts,fnt_pts,c_black);
  }
  if (collisionCheckName(player,"fruit")!=NULL){
    soundPlay(snd_cherry);
    musicPlay(msc_ghost,-1);
    blue=true;
    destroy(other);
    points+=500;
    //sprintf(pts,"%d",points);
    sprintf(pts,"%d",fps);
    updateText(txt_points,pts,fnt_pts,c_black);
  }
  if (collisionCheckName(player,"phantom")!=NULL){
    if (other->sprite_index!=spr_pblue){
    return 0;
    }else{
      soundPlay(snd_ghost);
      destroy(other);
    }
  }
  if (!instanceExists("Point",room) && !instanceExists("fruit",room)){
    return 1;
  }
  drawScene(room,cmr,"Room2");
  }
}
