#include "Input.h"

void Input::Update()
{
	prevLeft = curLeft;
	prevRight = curRight;
	prevDown = curDown;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			quit = true;
		}
	}
	keyState = SDL_GetKeyboardState(nullptr);
	curLeft = keyState[SDL_SCANCODE_LEFT];
	curRight = keyState[SDL_SCANCODE_RIGHT];
	curDown = keyState[SDL_SCANCODE_DOWN];
}

bool Input::MoveLeft()
{
	return curLeft && !prevLeft;
}

bool Input::MoveRight()
{
	return curRight && !prevRight;
}

bool Input::MoveDown()
{
	return curDown && !prevDown;
}