#include "swarm.h"

#ifndef SCREEN_H
#define SCREEN_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern Uint32 *main_buffer;
extern Uint32 *blur_buffer;
extern SDL_Event event;

void init_SDL_Screen();
void init_Window();
void init_Renderer();
void init_Texture();
void init_buffers();
void update_screen();
void Load_Swarm(Swarm *swarm);
void box_blur();
void get_avg_color(int x, int y, Uint8 *red, Uint8 *green, Uint8 *blue);
void set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
void load_particle(Particle *particles);
int quit_program();
void close_program();

#endif // SCREEN_H
