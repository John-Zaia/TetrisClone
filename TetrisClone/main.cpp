#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include "Tetromino.h"
#include "Input.h"
#include "Grid.h"

int main(int argc, char* argv[]) {
    bool done = false;
    SDL_Init(SDL_INIT_VIDEO);        

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window* window;
    window = SDL_CreateWindow(
        "An SDL3 window",
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (window == NULL) {

        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    
    InitGrid();
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

        renderTetrisGrid(renderer);
        renderBoard(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
