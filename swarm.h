#ifndef SWARM_H_
#define SWARM_H_

#include "particle.h"

const int N_PARTICLES = 5000;
typedef struct Swarm Swarm;

struct Swarm
{
  int last_clock;
  Particle *m_particle_array;
};

Swarm Swarm_create();
void Swarm_destroy(Swarm *swarm);
void Swarm_move(Swarm *swarm, int elapsed);
Particle *Swarm_get_particles(const Swarm *swarm);

#endif // SWARM_H_