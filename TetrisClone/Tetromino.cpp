#include "Tetromino.h"
#include <random>

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

Rectangle::Rectangle()
{
    vertices = {
        {{50, 130}, {0, 255, 255, 255}, {0,0}},//top left
        {{70, 130}, {0, 255, 255, 255}, {0,0}},//top right
        {{50, 50}, {0, 255, 255, 255}, {0,0}},//bottom left
        {{70, 50}, {0, 255, 255, 255}, {0,0}},//bottom right
    };

    indices = {
        0, 2, 3, //first triangle
        0, 1, 3, //second triangle
    };
}


TShape::TShape()
{
    vertices = {
    //top square
        {{70, 70}, {255, 0, 255, 255}, {0,0}},//top left
        {{90, 70}, {255, 0, 255, 255}, {0,0}},//top right
        {{70, 50}, {255, 0, 255, 255}, {0,0}},//bottom left
        {{90, 50}, {255, 0, 255, 255}, {0,0}},//bottom right

    //bottom rectangle
        {{50, 90}, {255, 0, 255, 255}, {0,0}},//top left
        {{110, 90}, {255, 0, 255, 255}, {0,0}},//top right
        {{50, 70}, {255, 0, 255, 255}, {0,0}},//bottom left
        {{110, 70}, {255, 0, 255, 255}, {0,0}},//bottom right
    };


    indices = {
        //top square
        0, 2, 3, //first triangle
        0, 1, 3, //second triangle

        //bottom rectangle
        4, 6, 7,//first triangle
        4, 5, 7,//second triangle
    };
}

SShape::SShape()
{
    vertices = {
        //top rectangle
            {{70, 70}, {0, 255, 0, 255}, {0,0}},//top left
            {{110, 70}, {0, 255, 0, 255}, {0,0}},//top right
            {{70, 50}, {0, 255, 0, 255}, {0,0}},//bottom left
            {{110, 50}, {0, 255, 0, 255}, {0,0}},//bottom right

        //bottom rectangle
            {{50, 90}, {0, 255, 0, 255}, {0,0}},//top left
            {{90, 90}, {0, 255, 0, 255}, {0,0}},//top right
            {{50, 70}, {0, 255, 0, 255}, {0,0}},//bottom left
            {{90, 70}, {0, 255, 0, 255}, {0,0}},//bottom right
    };

    indices = {
        //top rectangle
        0, 2, 3, //first triangle
        0, 1, 3, //second triangle

        //bottom rectangle
        4, 6, 7,//first triangle
        4, 5, 7,//second triangle
    };
}


LShape::LShape()
{
    vertices = {
        //left rectangle
        {{50, 110}, {255, 165, 0, 255}, {0,0}},//top left
        {{70, 110},{255, 165, 0, 255}, {0,0}},//top right
        {{50, 50}, {255, 165, 0, 255}, {0,0}},//bottom left
        {{70, 50},{255, 165, 0, 255}, {0,0}},//bottom right

        //bottom-right square
        {{70, 110}, {255, 165, 0, 255}, {0,0}},//top left
        {{90, 110}, {255, 165, 0, 255}, {0,0}},//top right
        {{70, 90}, {255, 165, 0, 255}, {0,0}},//bottom left
        {{90, 90}, {255, 165, 0, 255}, {0,0}},//bottom right
    };

    indices = {
        //left rectangle
        0, 2, 3, //first triangle
        0, 1, 3, //second triangle

        //bottom-right square
        4, 6, 7,//first triangle
        4, 5, 7,//second triangle
    };
}


void Gravity(Tetromino& t)
{
    Uint64 currentTime = SDL_GetTicks();

    if (currentTime - t.lastTime >= 1000)
    {
        for (int i = 0; i < static_cast<int>(t.vertices.size()); i++)
        {
            t.vertices[i].position.y += 20.0f;
        }
        t.lastTime = currentTime;
    }
}

Tetromino generateRandomTetromino()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 5);
    int randomNumber = distrib(gen);

    if (randomNumber == 1)
    {
        Square square;
        return square;
    }
    else if (randomNumber == 2)
    {
        Rectangle rectangle;
        return rectangle;
    }
    else if (randomNumber == 3)
    {
        TShape tShape;
        return tShape;
    }
    else if (randomNumber == 4)
    {
        SShape sShape;
        return sShape;
    }
    else
    {
        LShape lShape;
        return lShape;
    }
}

const float GRID_ORIGIN_X = 50.0f;
const float GRID_ORIGIN_Y = 50.0f;
const int   GRID_COLS = 10;
const int   GRID_ROWS = 20;
const float CELL_SIZE = 20.0f;

Bounds getBounds(const Tetromino& t)
{
    float minX = t.vertices[0].position.x;
    float maxX = t.vertices[0].position.x;
    float minY = t.vertices[0].position.y;
    float maxY = t.vertices[0].position.y;

    for (const auto& v : t.vertices)
    {
        minX = SDL_min(minX, v.position.x);
        maxX = SDL_max(maxX, v.position.x);
        minY = SDL_min(minY, v.position.y);
        maxY = SDL_max(maxY, v.position.y);
    }

    return Bounds{ minX, maxX, minY, maxY };
}

bool hitsFloor(const Tetromino& t)
{
    Bounds b = getBounds(t);
    return b.bottom >= GRID_ORIGIN_Y + GRID_ROWS * CELL_SIZE; 
}

bool canMoveHorizontal(const Tetromino& t, float dx)
{
    Bounds b = getBounds(t);
    float newLeft = b.left + dx;
    float newRight = b.right + dx;
    return newLeft >= GRID_ORIGIN_X && newRight <= GRID_ORIGIN_X + GRID_COLS * CELL_SIZE;
}