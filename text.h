#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

font *newFont(char *font_file,int size);
sprite *newText(char *string,font *text_font,SDL_Color clr);
void addTextSequence(sprite *spr,char *string,font *text_font,SDL_Color clr);

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
     subaux->img[0]=text;
     subaux->img[1]=text;
     subaux->img[2]=text;
     subaux->img[3]=text;
     subaux->prox=NULL;
     aux->size=1;
     aux->sub=1;
     aux->time=0;
     aux->start=subaux;
     aux->last=subaux;
     return aux;
}

void updateText(sprite *spr,char *string,font *text_font,SDL_Color clr){
  SDL_Surface *text;
  text = TTF_RenderText_Solid(text_font->font, string, clr);
  spr->start->img[0]=text;
  spr->start->img[1]=text;
  spr->start->img[2]=text;
  spr->start->img[3]=text;
}

void addTextSequence(sprite *spr,char *string,font *text_font,SDL_Color clr){
  SDL_Surface *text;
  text = TTF_RenderText_Solid(text_font->font, string, clr);
  spr->size++;
  subimg *aux;
  subimg *new_sub;
  new_sub=(subimg*)malloc(sizeof(subimg));
  new_sub->img[0]=text;
  new_sub->img[1]=text;
  new_sub->img[2]=text;
  new_sub->img[3]=text;
  new_sub->prox=NULL;
  aux=spr->last;
  aux->prox=new_sub;
  spr->last=new_sub;
}
#endif // TEXT_H_INCLUDED
