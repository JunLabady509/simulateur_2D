#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "swarm.h"
#include "particle.h"

int main(int argc, char *argv[])
{
    // Init the SDL
    init_SDL_Screen();
    init_Window();
    init_Renderer();
    init_Texture();

    // Generate the swarm
    Swarm swarm = Swarm_create();

    while(!quit_program)
    {
        // Update particles
        int elapsed = SDL_GetTicks();
        Swarm_move(&swarm, elapsed);

        // Draw particles
        const Particle *const particles = Swarm_get_particles(&swarm);
        for (int i = 0; i < N_PARTICLES; ++i)
        {
            Particle particle = particles[i];
            int x = (particle.m_x + 1) * SCREEN_WIDTH / 2;
            int y = particle.m_y * SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2;
            set_Pixel(x, y, red, green, blue);
        }

        // Update the screen
        update_Screen();

        // Check for messages/events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit_program = true;
            }
        }
    }

}
