#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else
  {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) // did snake hit body
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
      hit_tail = true;
    }
  }

  if (current_head_cell.x == 0 or current_head_cell.x == grid_width - 1 or current_head_cell.y == 0 or current_head_cell.y == grid_height - 1)
  {
    alive = false;
    hit_wall = true;
  }
}

void Snake::GrowBody() { growing = true; }

// Updated efficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  SDL_Point const current_cell{x, y};

  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }

  for (auto const &item : body)
  {
    if (current_cell.x == item.x && current_cell.y == item.y)
    {
      return true;
    }
  }
  return false;
}
