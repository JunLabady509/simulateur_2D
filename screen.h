#include "swarm.h"

#ifndef SCREEN_H
#define SCREEN_H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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
