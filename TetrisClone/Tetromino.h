#pragma once
#include <SDL3/SDL.h>
#include <array>

struct CellOffset
{
    int row;
    int col;
};

class Tetromino
{
public:
    int anchorRow = 0;
    int anchorCol = 4;
    std::array<CellOffset, 4> cells;
    int colorId = 1;
    Uint64 lastTime = SDL_GetTicks();

    std::array<CellOffset, 4> OccupiedCells() const
    {
        std::array<CellOffset, 4> result;
        for (int i = 0; i < 4; i++)
            result[i] = { anchorRow + cells[i].row, anchorCol + cells[i].col };
        return result;
    }

    void Render(SDL_Renderer* renderer) const;
};

class Square : public Tetromino { public: Square(); };
class Rectangle : public Tetromino { public: Rectangle(); };
class TShape : public Tetromino { public: TShape(); };
class SShape : public Tetromino { public: SShape(); };
class LShape : public Tetromino { public: LShape(); };

bool hitsFloor(const Tetromino& t);
bool canMoveHorizontal(const Tetromino& t, int dCol);
bool collidesWithBoard(const Tetromino& t);
void lockPiece(const Tetromino& t);
void Gravity(Tetromino& t);
Tetromino generateRandomTetromino();