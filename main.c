#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include <stdbool.h>
#include "particle.h"
#include <math.h>

int main(void)
{
    // Init the SDL
    init_SDL_Screen();
    init_Window();
    init_Renderer();
    init_Texture();

    // Generate the swarm
    Swarm * swarm = Swarm_create();

    bool is_running = false;
    while (!is_running)
    {
        // Update particles
        int elapsed = SDL_GetTicks();
        Swarm_move(swarm, elapsed);

        // Draw particles
        const Particle *const particles = Swarm_get_particles(swarm);
        for (int i = 0; i < N_PARTICLES; ++i)
        {
            Particle particle = particles[i];
            int x = (particle.m_x_cord + 1) * SCREEN_WIDTH / 2;
            int y = particle.m_y_cord * SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2;
            Uint8 red = (1 + sin(elapsed * 0.0001)) * 128;
            Uint8 green = (1 + sin(elapsed * 0.0002)) * 128;
            Uint8 blue = (1 + sin(elapsed * 0.0003)) * 128;
            set_pixel(x, y, red, green, blue);
        }

        // Update the screen
        update_screen();

        // Check for messages/events
        quit_program();
    }
}
