#include "Tetromino.h"
#include "Grid.h"
#include <random>

void Tetromino::Render(SDL_Renderer* renderer) const
{
    switch (colorId)
    {
    case 1: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;   // red
    case 2: SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); break; // cyan
    case 3: SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); break; // purple
    case 4: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break;   // green
    case 5: SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break; // orange
    default: SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); break;
    }

    for (auto& cell : OccupiedCells())
    {
        SDL_FRect rect = {
            GRID_ORIGIN_X + cell.col * CELL_SIZE,
            GRID_ORIGIN_Y + cell.row * CELL_SIZE,
            CELL_SIZE,
            CELL_SIZE
        };
        SDL_RenderFillRect(renderer, &rect);
    }
}

Square::Square()
{
    cells = { { {0,0}, {0,1}, {1,0}, {1,1} } };
    colorId = 1;
}

Rectangle::Rectangle()
{
    cells = { { {0,0}, {1,0}, {2,0}, {3,0} } };
    colorId = 2;
}

TShape::TShape()
{
    cells = { { {0,0}, {0,1}, {0,2}, {1,1} } };
    colorId = 3;
}

SShape::SShape()
{
    cells = { { {0,1}, {0,2}, {1,0}, {1,1} } };
    colorId = 4;
}

LShape::LShape()
{
    cells = { { {0,0}, {1,0}, {2,0}, {2,1} } };
    colorId = 5;
}

void Gravity(Tetromino& t)
{
    Uint64 currentTime = SDL_GetTicks();
    if (currentTime - t.lastTime >= 1000)
    {
        t.anchorRow += 1;
        t.lastTime = currentTime;
    }
}

Tetromino generateRandomTetromino()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 5);
    int randomNumber = distrib(gen);

    if (randomNumber == 1) { Square s; return s; }
    else if (randomNumber == 2) { Rectangle r; return r; }
    else if (randomNumber == 3) { TShape t; return t; }
    else if (randomNumber == 4) { SShape s; return s; }
    else { LShape l; return l; }
}

bool hitsFloor(const Tetromino& t)
{
    for (auto& cell : t.OccupiedCells())
        if (cell.row + 1 >= GRID_ROWS)
            return true;
    return false;
}

bool canMoveHorizontal(const Tetromino& t, int dCol)
{
    for (auto& cell : t.OccupiedCells())
    {
        int newCol = cell.col + dCol;
        if (newCol < 0 || newCol >= GRID_COLS)
            return false;
    }
    return true;
}

bool collidesWithBoard(const Tetromino& t)
{
    for (auto& cell : t.OccupiedCells())
    {
        if (cell.row + 1 >= GRID_ROWS) continue;
        if (board[cell.row + 1][cell.col] != 0)
            return true;
    }
    return false;
}

void lockPiece(const Tetromino& t)
{
    for (auto& cell : t.OccupiedCells())
        board[cell.row][cell.col] = t.colorId;
}