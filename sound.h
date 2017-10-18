#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

typedef struct sound{
Mix_Chunk *audio;
int channel;
}sound;

typedef struct music{
Mix_Music *audio;
int channel;
}music;

void audioStart(int audio_rate,Uint16 audio_format,int audio_channels);
sound *addSound(char *file);
music *addMusic(char *file);
void soundPlay(sound *snd);
void musicPlay(music *snd,int times);
bool soundIsPlaying(sound *snd);

void audioStart(int audio_rate,Uint16 audio_format,int audio_channels){
  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) != 0) {
   printf("Nao foi possivel inicializar o sistema de audio: %s\n", Mix_GetError());
  }
}

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

#endif // SOUND_H_INCLUDED
