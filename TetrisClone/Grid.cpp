#include "Grid.h"

int board[GRID_ROWS][GRID_COLS];

void InitGrid()
{
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int col = 0; col < GRID_COLS; col++)
		{
			board[row][col] = 0;
		}
	}
}

void renderBoard(SDL_Renderer* renderer)
{
	for (int row = 0; row < GRID_ROWS; row++)
	{
		for (int col = 0; col < GRID_COLS; col++)
		{
			if (board[row][col] == 0) continue;

			SDL_FRect cellRect = {
				GRID_ORIGIN_X + col * CELL_SIZE,
				GRID_ORIGIN_Y + row * CELL_SIZE,
				CELL_SIZE,
				CELL_SIZE
			};

			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			SDL_RenderFillRect(renderer, &cellRect);
		}
	}
}

void renderTetrisGrid(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_FRect outlineRect = {
		GRID_ORIGIN_X - 1,
		GRID_ORIGIN_Y - 1,
		GRID_COLS * CELL_SIZE + 2,
		GRID_ROWS * CELL_SIZE + 2
	};
	SDL_RenderRect(renderer, &outlineRect);

	for (int row = 0; row <= GRID_ROWS; row++)
	{
		float y = GRID_ORIGIN_Y + row * CELL_SIZE;
		SDL_RenderLine(renderer, GRID_ORIGIN_X, y, GRID_ORIGIN_X + GRID_COLS * CELL_SIZE, y);
	}

	for (int col = 0; col <= GRID_COLS; col++)
	{
		float x = GRID_ORIGIN_X + col * CELL_SIZE;
		SDL_RenderLine(renderer, x, GRID_ORIGIN_Y, x, GRID_ORIGIN_Y + GRID_ROWS * CELL_SIZE);
	}
}