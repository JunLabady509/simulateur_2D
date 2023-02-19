#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "screen.h"
#include "swarm.h"

#define false 0
#define true 1

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
Uint32 *main_buffer = NULL;
Uint32 *blur_buffer = NULL;
SDL_Event event;

// Initialize the SDL_Screen
void init_SDL_Screen()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf(">> SDL_Init Error : %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

// Create the SDL_Screen
void init_Window()
{
  window = SDL_CreateWindow(
      "2D Graphic Simulator",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_ALLOW_HIGHDPI);

  if (window == NULL)
  {
    printf(">> SDL_CreateWindow Error : %s", SDL_GetError());
  }
}

// Create the SDL_Renderer
void init_Renderer()
{
  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_PRESENTVSYNC |
          SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf(">> SDL_Renderer Error : %s", SDL_GetError());
    SDL_DestroyWindow(window); // Destroy the window
    exit(EXIT_FAILURE);
  }
}

// Initialize the SDL_Texture
void init_Texture()
{
  texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STREAMING,
      SCREEN_WIDTH,
      SCREEN_HEIGHT);
  if (texture == NULL)
  {
    printf(">> SDL_CreateTexture Error : %s", SDL_GetError());
    SDL_DestroyRenderer(renderer); // Destroy the renderer
    SDL_DestroyWindow(window);     // Destroy the window
    exit(EXIT_FAILURE);
  }
}

void init_buffers()
{
  // Create the main buffer and the blur buffer


  main_buffer = (uint32_t*) calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(uint32_t));
  blur_buffer = (uint32_t*) calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(uint32_t));

  if (main_buffer == NULL || blur_buffer == NULL)
  {
    printf(">> malloc Error : %s", SDL_GetError());
    SDL_DestroyTexture(texture);   // Destroy the texture
    SDL_DestroyRenderer(renderer); // Destroy the renderer
    SDL_DestroyWindow(window);     // Destroy the window
    exit(EXIT_FAILURE);            // Close the program with an error
  }

  // Initialize the buffers with black color
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
  {
    main_buffer[i] = 0x00000000; // black
    blur_buffer[i] = 0x00000000; // black
  }

}

// Update the screen using the main buffer
void update_screen()
{
  SDL_UpdateTexture(
      texture,
      NULL,
      main_buffer,
      SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer,
                 texture,
                 NULL,
                 NULL);
  SDL_RenderPresent(renderer);
}

void set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
  {
    return;
  }

  Uint32 color = 0;

  color += red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;
  color <<= 8;
  color += 0xFF;

  main_buffer[(y * SCREEN_WIDTH) + x] = color;
}

void Load_Swarm(Swarm *swarm)
{
  // Load the swarm particles
  const Particle *const particles = Swarm_get_particles(swarm);

  // generate colors to update swarm.
  int elapsed = SDL_GetTicks();
  unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
  unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
  unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

  // Load swarm with updated colors.
  for (int i = 0; i < N_PARTICLES; ++i)
  {
    Particle particle = particles[i];

    int x = (particle.m_x_cord + 1) * SCREEN_WIDTH / 2;
    int y = particle.m_y_cord * SCREEN_WIDTH / 2 + SCREEN_HEIGHT / 2;

    set_pixel(x, y, red, green, blue);
  }
}

void box_blur()
{
  // Main_buffer and blur_buffer are swapped, blur is applied to blur_buffer, and then
  // during each next iteration buffers are swapped again to display the blur effect on screen.

  // Swap the buffers
  Uint32 *temp = main_buffer;
  main_buffer = blur_buffer;
  blur_buffer = temp;

  // Apply the blur effect
  for (int y = 0; y < SCREEN_HEIGHT; ++y)
  {
    for (int x = 0; x < SCREEN_WIDTH; ++x)
    {
      Uint8 red = 0;
      Uint8 green = 0;
      Uint8 blue = 0;
      get_avg_color(x, y, &red, &green, &blue);
      set_pixel(x, y, red, green, blue);
    }
  }
}

void get_avg_color(int x, int y, Uint8 *red, Uint8 *green, Uint8 *blue)
{
  int total_red = 0;
  int total_green = 0;
  int total_blue = 0;

  for (int row = -1; row <= 1; ++row)
  {
    for (int col = -1; col <= 1; ++col)
    {
      int current_x = x + col;
      int current_y = y + row;

      if (current_x >= 0 && current_x < SCREEN_WIDTH && current_y >= 0 && current_y < SCREEN_HEIGHT)
      {
        Uint32 color = blur_buffer[current_y * SCREEN_WIDTH + current_x];
        Uint8 red = color >> 24;
        Uint8 green = color >> 16;
        Uint8 blue = color >> 8;

        total_red += red;
        total_green += green;
        total_blue += blue;
      }
    }
  }

  *red = total_red / 9;
  *green = total_green / 9;
  *blue = total_blue / 9;
}

// A function that check for SDL events.
// If the window is closed, quit the program.
int quit_program()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      return 1;
    }
  }
  return 0;
}

// Free the memory and close the program
void close_program()
{
  SDL_DestroyTexture(texture);   // Destroy the texture
  SDL_DestroyRenderer(renderer); // Destroy the renderer
  SDL_DestroyWindow(window);     // Destroy the window
  SDL_Quit();                    // Close the SDL
}