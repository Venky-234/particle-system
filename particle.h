#include "src\raylib.h"
#include <time.h>
typedef struct particle{
    Vector2 p_position;
    Vector2 p_dimension;
    Vector2 p_velocity;
    float p_rotation;
    Color p_color;
    time_t init_time;
}particle;

void render_particle(particle p);
void apply_velocity(particle *p);
void apply_gravity(particle *p);