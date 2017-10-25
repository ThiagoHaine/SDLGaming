#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED


sound *addSound(char *file);
music *addMusic(char *file);
void soundPlay(sound *snd);
void musicPlay(music *snd,int times);
bool soundIsPlaying(sound *snd);

sound *addSound(char *file){
sound *aux;
aux=(sound*)malloc(sizeof(sound));
aux->audio=Mix_LoadWAV(file);
if (!aux->audio){
  printf("Error en Mix_LoadWAV: %s\n", Mix_GetError());
}
aux->channel=0;
return aux;
}

music *addMusic(char *file){
music *aux;
aux=(music*)malloc(sizeof(music));
aux->audio=Mix_LoadMUS(file);
if (!aux->audio){
  printf("Error en Mix_LoadMUS: %s\n", Mix_GetError());
}
aux->channel=0;
return aux;
}

void soundPlay(sound *snd){
snd->channel = Mix_PlayChannel(-1, snd->audio, 0);
if (snd->channel == -1) {
   printf("Impossível reproduzir arquivo WAV: %s\n", Mix_GetError());
}
}

void musicPlay(music *snd,int times){
snd->channel = Mix_PlayMusic(snd->audio, times);
if (snd->channel == -1) {
   printf("Impossível reproduzir arquivo WAV: %s\n", Mix_GetError());
}
}

bool soundIsPlaying(sound *snd){
  if (Mix_Playing(snd->channel)==0){
    return false;
  }else{
    return true;
  }
}

bool musicIsPlaying(){
  if (Mix_PlayingMusic()==0){
    return false;
  }else{
    return true;
  }
}

void soundStop(sound *snd){
  if (soundIsPlaying(snd)){
    Mix_HaltChannel(snd->channel);
  }
}

void musicStop(){
  Mix_HaltMusic();
}
#endif // SOUND_H_INCLUDED
