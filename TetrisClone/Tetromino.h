#include <SDL3/SDL.h>
#include <vector>
#pragma once

class Tetromino
{
    public:
        std::vector<SDL_Vertex> vertices;
        std::vector<int> indices;
        virtual ~Tetromino() = default;
        Uint64 lastTime = SDL_GetTicks();
        void Render(SDL_Renderer* renderer);
};

class Square : public Tetromino
{
    public:
        Square();
};

class Rectangle : public Tetromino
{
    public:
        Rectangle();
};


class TShape : public Tetromino
{
    public:
        TShape();
};

class SShape : public Tetromino
{
    public:
        SShape();
};


class LShape : public Tetromino
{
    public:
        LShape();
};

void Gravity(Tetromino& t);