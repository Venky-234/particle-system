#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "src\raylib.h"
#include "particle.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 450;

float particle_spread = 2;
float release_time = 10;
float color_cycle_speed = 4;

bool is_gravity_applied = false;
bool is_randomize_color = false;
bool color_cycle = false;

Color particle_color;

int r = 255;
int g,b = 0;
int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,"particle_system");
    SetTargetFPS(60);
    
    particle smoke[10000];
    time_t init_time = clock();
    particle_color = RED;

    int index = 0;
    int random_delay = GetRandomValue(0, 100);
     
    for(int i = 0; i < sizeof(smoke)/sizeof(particle); i++){
        smoke[i].p_color = particle_color; //(Color){random_white, random_white, random_white,255};
        smoke[i].p_dimension = (Vector2){10,10};
        smoke[i].p_position = (Vector2){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2};
        smoke[i].p_velocity = (Vector2){0,0};
        smoke[i].p_rotation = GetRandomValue(0, 360);
        smoke[i].init_time = NULL;
    }         
    
    Texture2D tex = LoadTexture("car.png");
    while(!WindowShouldClose()){
        BeginDrawing();
        
        if((clock() - init_time)* 1000 / CLOCKS_PER_SEC > release_time){
            if(smoke[index].p_dimension.x == 0){
                smoke[index].p_position = (Vector2){SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2};
                smoke[index].p_dimension = (Vector2){10,10};
            }
            random_delay = GetRandomValue(10, 90);
            init_time = clock();
            smoke[index].p_velocity.x = GetRandomValue(-particle_spread, particle_spread);
            smoke[index].p_velocity.y = GetRandomValue(-1,-3);
            smoke[index].init_time = clock();
            if(is_randomize_color)
                smoke[index].p_color = (Color){
                    GetRandomValue(0,255),
                    GetRandomValue(0,255),
                    GetRandomValue(0,255),
                    255
                }; 
            else
                smoke[index].p_color = particle_color;//(Color){random_white, random_white, random_white,255};
            index++;
            if(index > sizeof(smoke)/sizeof(particle)) index = 0;

        }
        for(int i = 0; i < sizeof(smoke)/sizeof(particle); i++){
            if(smoke[i].init_time != NULL){
                if((clock() - smoke[i].init_time)* 1000 /CLOCKS_PER_SEC > 150){
                    smoke[i].init_time = clock();
                    if (smoke[i].p_dimension.x > 0) smoke[i].p_dimension.x -= 1;
                    if (smoke[i].p_dimension.y > 0) smoke[i].p_dimension.y -= 1;
                    if (smoke[i].p_color.a > 0) smoke[i].p_color.a -= 30;
                }
            }
        }
        for(int i = 0; i < sizeof(smoke)/sizeof(particle); i++){
            apply_velocity(&smoke[i]);
            //if(smoke[i].p_velocity.x != 0 && smoke[i].p_velocity.y != 0)
            if(smoke[i].init_time != NULL){
                if(is_gravity_applied)
                    apply_gravity(&smoke[i]);
                
                render_particle(smoke[i]);
            }
            smoke[i].p_rotation += 10;
        }
        DrawLine(500, 0, 500, GetScreenHeight(), Fade(LIGHTGRAY, 0.2f));
        DrawRectangle(500,0, SCREEN_WIDTH - 500, SCREEN_HEIGHT, Fade(WHITE, 0.9f));
        DrawFPS(10,10);

        GuiSliderBar((Rectangle){ 600, 40, 120, 20 }, "particle_spread", NULL, &particle_spread, 0, 5);
        GuiSliderBar((Rectangle){ 620, 90, 120, 20 }, "paticle delay", NULL, &release_time, 0,100);
        GuiCheckBox((Rectangle){ 600,360, 20, 20 }, "apply gravity", &is_gravity_applied); 
        
        if(GuiCheckBox((Rectangle){ 600, 390, 20, 20 }, "randomize color", &is_randomize_color)){
            if(is_randomize_color)
                color_cycle = false;
        }
        
        if(GuiCheckBox((Rectangle){ 600, 420, 20, 20 }, "color cycle", &color_cycle)){
            if(color_cycle)
                is_randomize_color = false;
           
        }
        
        if(!is_randomize_color && !color_cycle)
            GuiColorPicker((Rectangle){550,140,200,200},"color picker",&particle_color);


        if (color_cycle){
            GuiSliderBar((Rectangle){ 600, 140, 120, 20 }, "cycle speed", NULL, &color_cycle_speed, 0,25);
            particle_color = (Color){r,g,b,255};
            if(g == 255 && r != 0){
                r -= color_cycle_speed;
                if(r < 0)
                    r = 0;
            }

            if(r == 255 && b == 0 && g != 255){
                g += color_cycle_speed;
                if(g > 255)
                    g = 255;
            }
            
            if(r == 0 && b != 255){
                b += color_cycle_speed;
                if(b > 255)
                    b = 255;
            }
            
            if(b == 255 && g != 0){
                g -= color_cycle_speed;
                if(g < 0)
                    g = 0;
            }
            
            if(g == 0 && r != 255){
                r += color_cycle_speed;
                if(r > 255)
                    r = 255;
            }
            
            if(r == 255 && g ==0 && b != 0){
                b -= color_cycle_speed;
                if(b < 0)
                    b = 0;
            }
        }

        ClearBackground(BLACK);
        EndDrawing();
    }
}