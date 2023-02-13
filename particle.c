#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "particle.h"

#define M_PI 3.14159265358979323846

void initialize(Particle *particle)
{
  double speed_min = -1;
  double speed_max = 1;
  double angle_min = 0;
  double angle_max = 2 * M_PI;

  particle->m_x_cord = 0;
  particle->m_y_cord = 0;

  double speed = pow(((double)rand() / RAND_MAX) * (speed_max - speed_min) + speed_min, 2) * 0.04;
  double direction = ((double)rand() / RAND_MAX) * (angle_max - angle_min) + angle_min;

  particle->m_speed = speed;
  particle->m_direction = direction;
}

void move_particle(Particle *particle, int interval)
{
  particle->m_direction += (interval * 0.0005);
  particle->m_x_vector = particle->m_speed * sin(particle->m_direction);
  particle->m_y_vector = particle->m_speed * cos(particle->m_direction);
  particle->m_x_cord += (particle->m_x_vector * interval);
  particle->m_y_cord += (particle->m_y_vector * interval);

  if (particle->m_x_cord < -1 || particle->m_x_cord > 1 || particle->m_y_cord < -1 || particle->m_y_cord > 1)
  {
    initialize(particle);
  }
}