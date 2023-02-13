#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct Particle Particle;
struct Particle
{
  double m_x_cord;
  double m_y_cord;
  double m_speed;
  double m_direction;
  double m_x_vector;
  double m_y_vector;
};

void initialize(Particle *particle);

void move_particle(Particle *particle, int interval);

#endif // PARTICLE_H
