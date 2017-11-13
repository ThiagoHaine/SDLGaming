#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

sprite *newSprite(char *img_file);
void addSubimg(sprite *spr,char *img_file);
SDL_Surface *getImage(sceneElement *spr);
SDL_Surface *getSubimage(sprite *spr,int i);
Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
SDL_Surface *flip_surface( SDL_Surface *surface, int flags );

sprite *newSprite(char *img_file){
  sprite *aux;
  subimg *subaux;
  aux=(sprite*)malloc(sizeof(sprite));
  subaux=(subimg*)malloc(sizeof(subimg));
  subaux->img[0]=IMG_Load(img_file);
  subaux->img[1]=IMG_Load(img_file);
  subaux->img[1]=flip_surface( subaux->img[1], f_vertical );
  subaux->img[2]=IMG_Load(img_file);
  subaux->img[2]=flip_surface( subaux->img[2], f_horizontal );
  subaux->img[3]=IMG_Load(img_file);
  subaux->img[3]=flip_surface( subaux->img[3], f_horizontal | f_vertical );
  subaux->prox=NULL;
  aux->size=1;
  aux->sub=1;
  aux->time=0;
  aux->start=subaux;
  aux->last=subaux;
  return aux;
}

void addSubimg(sprite *spr,char *img_file){
  spr->size++;
  subimg *aux;
  subimg *new_sub;
  new_sub=(subimg*)malloc(sizeof(subimg));
  new_sub->img[0]=IMG_Load(img_file);
  new_sub->img[1]=IMG_Load(img_file);
  new_sub->img[1]=flip_surface( new_sub->img[1], f_vertical );
  new_sub->img[2]=IMG_Load(img_file);
  new_sub->img[2]=flip_surface( new_sub->img[2], f_horizontal );
  new_sub->img[3]=IMG_Load(img_file);
  new_sub->img[3]=flip_surface( new_sub->img[3], f_horizontal | f_vertical );
  new_sub->prox=NULL;
  aux=spr->last;
  aux->prox=new_sub;
  spr->last=new_sub;
}

SDL_Surface *getImage(sceneElement *inst){
        int atual=0;
        subimg *aux;
        int time_aux=0;
        while(atual<inst->sub){
          if (atual==0){
            aux=inst->sprite_index->start;
          }else{
            aux=aux->prox;
          }
          atual++;
        }
        if (inst->sprite_index->size>1){
        time_aux=fps/inst->sprite_speed;
        if ((time_aux%2)==0){
          time_aux--;
        }
        
        if ((fps_aux%time_aux)==0){
          if (inst->sub<inst->sprite_index->size){
            inst->sub++;
          }else{
            inst->sub=1;
          }
        }
          return aux->img[inst->flip];
        }else{
          return inst->sprite_index->start->img[inst->flip];
        }
}

SDL_Surface *getSubimage(sprite *spr,int i){

  int atual=0;
  subimg *aux;
  while(atual<i){
    if (atual==0){
      aux=spr->start;
    }else{
      aux=aux->prox;
    }
    atual++;
  }
  return aux->img[0];
}

Uint32 get_pixel32( SDL_Surface *surface, int x, int y ) { 
//Convert the pixels to 32 bit
Uint32 *pixels = (Uint32 *)surface->pixels;
//Get the requested pixel 
return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) {
//Convert the pixels to 32 bit
Uint32 *pixels = (Uint32 *)surface->pixels;
//Set the pixel
pixels[ ( y * surface->w ) + x ] = pixel;
}

SDL_Surface *flip_surface( SDL_Surface *surface, int flags )
{
  if (flags!=0){
    //Pointer to the soon to be flipped surface
    SDL_Surface *flipped = NULL;

    //If the image is color keyed
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    //Otherwise
    else
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    //If the surface must be locked
    if( SDL_MUSTLOCK( surface ) )
    {
        //Lock the surface
        SDL_LockSurface( surface );
    }

    //Go through columns
    for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
    {
        //Go through rows
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
        {
            //Get pixel
            Uint32 pixel = get_pixel32( surface, x, y );

            //Copy pixel
            if( ( flags & f_vertical ) && ( flags & f_horizontal ) )
            {
                put_pixel32( flipped, rx, ry, pixel );
            }
            else if( flags & f_horizontal )
            {
                put_pixel32( flipped, rx, y, pixel );
            }
            else if( flags & f_vertical )
            {
                put_pixel32( flipped, x, ry, pixel );
            }
        }
    }

    //Unlock surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }

    //Copy color key
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }

    //Return flipped surface
    return flipped;
  }else{
    return surface;
  }
}
#endif // SPRITE_H_INCLUDED
