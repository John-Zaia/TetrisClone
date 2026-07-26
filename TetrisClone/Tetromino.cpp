#include "Tetromino.h"

void Tetromino::Render(SDL_Renderer* renderer)
{
    SDL_RenderGeometry(
        renderer,
        nullptr,
        vertices.data(),
        vertices.size(),
        indices.data(),
        indices.size()
    );
}

Square::Square()
{
    vertices = {
    {{50, 90}, {255, 0, 0, 255}, {0,0}},//top left
    {{90, 90}, {255, 0, 0, 255}, {0,0}},//top right
    {{50, 50}, {255, 0, 0, 255}, {0,0}},//bottom left
    {{90, 50}, {255, 0, 0, 255}, {0,0}},//bottom right
    };

    indices = {
        0, 2, 3, //first triangle
        0, 1, 3, //second triangle
    };
}

void Gravity(Tetromino& t)
{
    static Uint64 lastTime = SDL_GetTicks();
    Uint64 currentTime = SDL_GetTicks();

    if (currentTime - lastTime >= 1000)
    {
        for (int i = 0; i < static_cast<int>(t.vertices.size()); i++)
        {
            t.vertices[i].position.y += 20.0f;
        }
        lastTime = currentTime;
    }
}