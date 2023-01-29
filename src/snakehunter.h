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
          head_x(grid_width / 2),
          head_y(grid_height / 2) {}

    void Update(Snake &snake);

    float speed{0.1f};
    int size{1};
    float head_x;
    float head_y;

private:
    void ChaseSnake(float head_x, float head_y, SDL_Point snake_cell);

    int grid_width;
    int grid_height;
};

#endif
