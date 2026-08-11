#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include "Tetromino.h"
#include "Input.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window;
SDL_Renderer* renderer;

void renderTetrisGrid()
{

    SDL_FRect outlineRect = { 49, 49, 201, 401 };
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1.0);

    SDL_RenderRect(renderer, &outlineRect);

    float x1 = 50.0f;
    float y1 = 70.0f;
    float x2 = 250.0f;
    float y2 = 70.0f;

    //Render horizontal lines
    for (int i = 0; i < 19; i++)
    {
        SDL_RenderLine(renderer, x1, y1, x2, y2);
        y1 += 20.0f;
        y2 += 20.0f;
    }

    //Render vertical lines
    float vx1 = 70.0f;
    float vy1 = 50.0f;
    float vx2 = 70.0f;
    float vy2 = 450.0f;
    for (int i = 0; i < 9; i++)
    {
        SDL_RenderLine(renderer, vx1, vy1, vx2, vy2);
        vx1 += 20.0f;
        vx2 += 20.0f;
    }
}   

int main(int argc, char* argv[]) {

 
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);        


    window = SDL_CreateWindow(
        "An SDL3 window",                 
        640,                            
        480,                      
        SDL_WINDOW_OPENGL       
    );

    renderer = SDL_CreateRenderer(window, NULL);

    if (window == NULL) {

        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    Tetromino randomTetromino;
    Input input;
    randomTetromino = generateRandomTetromino();

    while (!done) {
        input.Update();
            
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //background colour
        SDL_RenderClear(renderer);

        if (!hitsFloor(randomTetromino))
        {
            Gravity(randomTetromino);
        }

        randomTetromino.Render(renderer);


        if (input.MoveLeft() && canMoveHorizontal(randomTetromino, -20.0f))
        {
            for (int i = 0; i < static_cast<int>(randomTetromino.vertices.size()); i++)
            {
                    randomTetromino.vertices[i].position.x -= 20.0f;
            }
        }
        else if (input.MoveRight() && canMoveHorizontal(randomTetromino, +20.0f))
        {
            for (int i = 0; i < static_cast<int>(randomTetromino.vertices.size()); i++)
            {
                    randomTetromino.vertices[i].position.x += 20.0f;
            }
        }
        else if (input.MoveDown() && !hitsFloor(randomTetromino))
        {
            for (int i = 0; i < static_cast<int>(randomTetromino.vertices.size()); i++)
            {
                randomTetromino.vertices[i].position.y += 20.0f;
            }
        }

        renderTetrisGrid();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
