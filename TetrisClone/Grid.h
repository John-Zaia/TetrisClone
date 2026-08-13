#include <SDL3/SDL.h>
#pragma once

const float GRID_ORIGIN_X = 50.0f;
const float GRID_ORIGIN_Y = 50.0f;
const float CELL_SIZE = 20.0f;
const int GRID_COLS = 10;
const int GRID_ROWS = 20;
extern int board[GRID_ROWS][GRID_COLS];

void renderTetrisGrid(SDL_Renderer* renderer);
void renderBoard(SDL_Renderer* renderer);
void InitGrid();