#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "src/raylib.h"
#include "particle.h"

bool gameRunning = true;
int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 700;


int main(int argc, char *argv[]){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,"explosion_particle_system");
    SetTargetFPS(60);

    particle explosion[50];
    time_t init_time; 
    bool render_bomb = true;
    Texture2D bomb_texture = LoadTexture("bomb.png");
    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground((Color){25,25,25,255});
        DrawFPS(20,10);
        DrawText("press R to simulate an explosion", 20,40, 20, GRAY);
        if(IsKeyPressed(KEY_R)){
            for(int i = 0; i < sizeof(explosion)/sizeof(particle); i++){
                explosion[i].p_velocity.x = GetRandomValue(-10,10);   
                explosion[i].p_velocity.y = GetRandomValue(-6,6);

                explosion[i].p_color = (Color){252, 107, 3, 255};
                explosion[i].p_position = (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                explosion[i].p_dimension = (Vector2){10,10};
                explosion[i].p_rotation = GetRandomValue(0,360);
            }
            init_time = clock();
            render_bomb = false;
        }
        for(int i = 0; i < sizeof(explosion)/sizeof(particle); i++){
            apply_velocity(&explosion[i]);
            apply_gravity(&explosion[i]);
            render_particle(explosion[i]);

        }
        if((clock() - init_time)* 1000 / CLOCKS_PER_SEC > 100){
            for(int i = 0; i < sizeof(explosion)/sizeof(particle); i++){
                init_time = clock();
                if (explosion[i].p_dimension.x > 0) explosion[i].p_dimension.x -= 1;
                if (explosion[i].p_dimension.y > 0) explosion[i].p_dimension.y -= 1;
                if (explosion[i].p_color.a > 0) explosion[i].p_color.a -= 30;
            }
        }
        EndDrawing();
    }
}