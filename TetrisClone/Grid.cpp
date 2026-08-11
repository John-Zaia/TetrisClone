#include "Grid.h"

void renderTetrisGrid(SDL_Renderer* renderer)
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