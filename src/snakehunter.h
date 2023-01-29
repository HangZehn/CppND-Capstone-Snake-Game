#ifndef SNAKEHUNTER_H
#define SNAKEHUNTER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class SnakeHunter
{
public:
  SnakeHunter(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 8),
        head_y(grid_height / 8) {}

  void Update(Snake &snake);

  float speed{0.05f};
  float head_x;
  float head_y;

private:
  void ChaseSnake(SDL_Point snake_cell);

  int grid_width;
  int grid_height;
};

#endif
