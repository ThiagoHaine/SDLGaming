#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

font *newFont(char *font_file,int size);
sprite *newText(char *string,font *text_font,SDL_Color clr);
void addTextSequence(sprite *spr,char *string,font *text_font,int spd,SDL_Color clr);

font *newFont(char *font_file,int size){
  font *aux;
  aux=(font*)malloc(sizeof(font));
  aux->font = TTF_OpenFont(font_file, size);
  return aux;
}

sprite *newText(char *string,font *text_font,SDL_Color clr){
     SDL_Surface *text;
     text = TTF_RenderText_Solid(text_font->font, string, clr);
     sprite *aux;
     subimg *subaux;
     aux=(sprite*)malloc(sizeof(sprite));
     subaux=(subimg*)malloc(sizeof(subimg));
     subaux->img=text;
     subaux->prox=NULL;
     aux->size=1;
     aux->sub=1;
     aux->time=0;
     aux->speed=1;
     aux->start=subaux;
     aux->last=subaux;
     return aux;
}

void updateText(sprite *spr,char *string,font *text_font,SDL_Color clr){
  SDL_Surface *text;
  text = TTF_RenderText_Solid(text_font->font, string, clr);
  spr->start->img=text;
}

void addTextSequence(sprite *spr,char *string,font *text_font,int spd,SDL_Color clr){
  SDL_Surface *text;
  text = TTF_RenderText_Solid(text_font->font, string, clr);
  spr->size++;
  spr->speed=spd*10;
  subimg *aux;
  subimg *new_sub;
  new_sub=(subimg*)malloc(sizeof(subimg));
  new_sub->img=text;
  new_sub->prox=NULL;
  aux=spr->last;
  aux->prox=new_sub;
  spr->last=new_sub;
}
#endif // TEXT_H_INCLUDED
