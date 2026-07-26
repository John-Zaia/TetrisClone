#include <SDL3/SDL.h>
#include <vector>
#pragma once

class Tetromino
{
    public:
        std::vector<SDL_Vertex> vertices;
        std::vector<int> indices;
        virtual ~Tetromino() = default;
        void Render(SDL_Renderer* renderer);
};

class Square : public Tetromino
{
    public:
        Square();
};

void Gravity(Tetromino& t);