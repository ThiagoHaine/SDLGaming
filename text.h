#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

font *newFont(char *font_file,int size){
  font *aux;
  aux=(font*)malloc(sizeof(font));
  aux->font = TTF_OpenFont(font_file, size);
  return aux;
}

void drawText(char *string,font *text_font, scene *scn){
     SDL_Surface *text;
     SDL_Color text_color={255,255,255};
     text = TTF_RenderText_Solid(text_font->font, string, text_color);
     SDL_BlitSurface(text, NULL, scn->video, NULL);
}
#endif // TEXT_H_INCLUDED
