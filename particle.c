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

#include "particle.h"
#include "src\raylib.h"
void render_particle(particle p){
    DrawRectanglePro(
        (Rectangle) {
            p.p_position.x,
            p.p_position.y,
            p.p_dimension.x,
            p.p_dimension.y
        },
        (Vector2){p.p_dimension.x/2 , p.p_dimension.y/2},
        p.p_rotation,
        p.p_color
    );
}

void apply_velocity(particle *p){
    p -> p_position.x += p -> p_velocity.x;
    p -> p_position.y += p -> p_velocity.y;

}
void apply_gravity(particle *p){
    p -> p_velocity.y += 0.1;
}
