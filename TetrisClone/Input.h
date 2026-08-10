#pragma once
#include <SDL3/SDL.h>

class Input
{
public:
	void Update();
	bool Quit() { return quit; }
	bool MoveLeft();
	bool MoveRight();
	bool MoveDown();

private:
	bool quit = false;
	const bool* keyState = nullptr;
	bool prevLeft = false, prevRight = false, prevDown = false;
	bool curLeft = false, curRight = false, curDown = false;
};


