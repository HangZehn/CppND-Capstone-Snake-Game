#include "snakehunter.h"
#include <cmath>
#include <iostream>

void SnakeHunter::Update(Snake &snake)
{
  SDL_Point hunter_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};

  SDL_Point snake_cell{
      static_cast<int>(snake.head_x),
      static_cast<int>(snake.head_y)};

  if (snake_cell.x == hunter_cell.x && snake_cell.y == hunter_cell.y)
  {
    snake.alive = false;
    rendezvous = true;
  }
  else
  {
    ChaseSnake(snake_cell);
  }
}

void SnakeHunter::ChaseSnake(SDL_Point snake_cell)
{
  // TODO pointer stuff

  float delta_x = snake_cell.x - head_x;
  float delta_y = snake_cell.y - head_y;
  float distance = sqrt(pow(snake_cell.x - head_x, 2) + pow(snake_cell.y - head_y, 2));
  head_x = head_x + delta_x / distance * speed;
  head_y = head_y + delta_y / distance * speed;
}
