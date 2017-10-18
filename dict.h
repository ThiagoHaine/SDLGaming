#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED
typedef enum { false, true } bool;

typedef struct object{
int time;
bool solid;
float hspeed;
float gravity;
struct sprite *sprite_index;
float vspeed;
char name[10];
}object;

typedef struct font{
TTF_Font *font;
}font;

typedef struct scene{
int idmax;
SDL_Surface * background;
bool fixed;
SDL_Surface * screen;
SDL_Surface * video;
SDL_Event event;
int bufferSize;
struct sceneElement *init;
struct sceneElement *end;
}scene;

typedef struct sceneElement{
scene *scn;
int id;
struct object *obj;
bool active;

struct sprite *sprite_index;
int sub;
int spr_time;
int sprite_speed;

int img;

int x;
int y;

int time;
bool solid;
float hspeed;
float gravity;
float vspeed;

struct sceneElement *prev;
struct sceneElement *next;
}sceneElement;

typedef struct camera{
  struct sceneElement *actor;
  int x;
  int y;
  int w;
  int h;
}camera;

typedef struct sprite{
int size;
int time;
int speed;
int sub;
struct subimg *start;
struct subimg *last;
}sprite;

typedef struct subimg{
SDL_Surface *img;
struct subimg *prox;
}subimg;


#define keyCheck key.keysym.sym
#define btnCheck button.button
#define color SDL_Color

#define e_quit SDL_QUIT
#define e_keydown SDL_KEYDOWN
#define e_keyup SDL_KEYUP
#define e_mousedown SDL_MOUSEBUTTONDOWN
#define e_mouseup SDL_MOUSEBUTTONUP
#define e_mouse SDL_MOUSEMOTION

//COLORS
SDL_Color c_black={0,0,0};
SDL_Color c_white={255,255,255};
SDL_Color c_red={255,0,0};
SDL_Color c_green={0,255,0};
SDL_Color c_blue={0,0,255};
SDL_Color c_gray={166,166,166};
SDL_Color c_orange={255,102,0};
SDL_Color c_pink={255,0,255};
SDL_Color c_yellow={255,255,0};
SDL_Color c_cyan={0,255,255};

SDL_Color c_ltred={255,153,153};
SDL_Color c_ltgreen={153,255,153};
SDL_Color c_ltblue={153,153,255};
SDL_Color c_ltgray={210,210,210};
SDL_Color c_ltorange={255,194,153};
SDL_Color c_ltpink={255,153,255};
SDL_Color c_ltyellow={255,255,153};
SDL_Color c_ltcyan={153,255,255};

SDL_Color c_dkred={100,0,0};
SDL_Color c_dkgreen={0,100,0};
SDL_Color c_dkblue={0,0,100};
SDL_Color c_dkgray={100,100,100};
SDL_Color c_dkorange={128,51,0};
SDL_Color c_dkpink={100,0,100};
SDL_Color c_dkyellow={100,100,0};
SDL_Color c_dkcyan={0,100,100};
/////////////


#define m_left SDL_BUTTON_LEFT
#define m_right SDL_BUTTON_RIGHT
#define m_middle SDL_BUTTON_MIDDLE
#define m_x motion.x
#define m_y motion.y

#define k_up SDLK_UP
#define k_left SDLK_LEFT
#define k_right SDLK_RIGHT
#define k_down SDLK_DOWN
#define k_enter SDLK_RETURN
#define k_backspace SDLK_BACKSPACE
#define k_esc SDLK_ESCAPE
#define k_space SDLK_SPACE
#define k_1 SDLK_1
#define k_2 SDLK_2
#define k_3 SDLK_3
#define k_4 SDLK_4
#define k_5 SDLK_5
#define k_6 SDLK_6
#define k_7 SDLK_7
#define k_8 SDLK_8
#define k_9 SDLK_9
#define k_a SDLK_a
#define k_b SDLK_b
#define k_c SDLK_c
#define k_d SDLK_d
#define k_e SDLK_e
#define k_f SDLK_f
#define k_g SDLK_g
#define k_h SDLK_h
#define k_i SDLK_i
#define k_j SDLK_j
#define k_k SDLK_k
#define k_l SDLK_l
#define k_m SDLK_m
#define k_n SDLK_n
#define k_o SDLK_o
#define k_p SDLK_p
#define k_q SDLK_q
#define k_r SDLK_r
#define k_s SDLK_s
#define k_t SDLK_t
#define k_u SDLK_u
#define k_v SDLK_v
#define k_w SDLK_w
#define k_x SDLK_x
#define k_y SDLK_y
#define k_z SDLK_z
#define k_f1 SDLK_F1
#define k_f2 SDLK_F2
#define k_f3 SDLK_F3
#define k_f4 SDLK_F4
#define k_f5 SDLK_F5
#define k_f6 SDLK_F6
#define k_f7 SDLK_F7
#define k_f8 SDLK_F8
#define k_f9 SDLK_F9
#define k_f10 SDLK_F10
#define k_f11 SDLK_F11
#define k_f12 SDLK_F12
#define k_lctrl SDLK_LCTRL
#define k_rctrl SDLK_RCTRL
#define k_lshift SDLK_LSHIFT
#define k_rshift SDLK_RSHIFT
#endif // DICT_H_INCLUDED
