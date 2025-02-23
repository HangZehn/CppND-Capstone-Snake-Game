#include "controller.h"
#include <iostream>
#include <memory>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(std::unique_ptr<Snake> &snake_ptr, Snake::Direction input,
                                 Snake::Direction opposite) const
{
  if (snake_ptr->direction != opposite || snake_ptr->size == 1)
    snake_ptr->direction = input;
  return;
}

void Controller::HandleInput(bool &running, std::unique_ptr<Snake> &snake_ptr) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        ChangeDirection(snake_ptr, Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake_ptr, Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake_ptr, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake_ptr, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
      }
    }
  }
}
