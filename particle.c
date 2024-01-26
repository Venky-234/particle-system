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