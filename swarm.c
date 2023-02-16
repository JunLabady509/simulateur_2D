#include <stdlib.h>
#include "swarm.h"
#include "particle.h"

const int N_PARTICLES = 5000;

Swarm *Swarm_create()
{
  Swarm * swarm = malloc(sizeof(Swarm));
  swarm->last_clock = 0;
  swarm->m_particle_array = malloc(N_PARTICLES * sizeof(Particle));
  return swarm;
}

void Swarm_destroy(Swarm *swarm)
{
  free(swarm->m_particle_array);
  free(swarm);
}

void Swarm_move(Swarm *swarm, int elapsed)
{
  int interval;
  if (swarm->last_clock == 0)
  {
    interval = 0;
  }
  else
  {
    interval = elapsed - swarm->last_clock;
  }
  swarm->last_clock = elapsed;

  for (int i = 0; i < N_PARTICLES; ++i)
  {
    move_particle(&swarm->m_particle_array[i], interval);
  }
}

Particle *Swarm_get_particles(const Swarm *swarm)
{
  return swarm->m_particle_array;
}
