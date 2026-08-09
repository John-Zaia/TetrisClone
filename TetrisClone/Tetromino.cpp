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

/*
LShape::LShape()
{

}
*/

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