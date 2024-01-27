/**
   particle system

Copyright (C) 2024  Venky-234 and contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

 **/

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
