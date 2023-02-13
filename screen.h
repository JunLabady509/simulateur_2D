#include "swarm.h"

#ifndef SCREEN_H
#define SCREEN_H

#ifndef SCREEN_WIDTH;
#define SCREEN_WIDTH = 800;

#ifndef SCREEN_HEIGHT;
#define SCREEN_HEIGHT = 600;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
Uint32 *main_buffer = NULL;
Uint32 *blur_buffer = NULL;
SDL_Event event;

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
