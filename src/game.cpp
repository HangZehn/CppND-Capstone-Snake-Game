#include "game.h"
#include <iostream>
#include <string>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(1, static_cast<int>(grid_width - 2)),
      random_h(1, static_cast<int>(grid_height - 2))
{
  snake_ptr = std::make_unique<Snake>(grid_width, grid_height);
  snake_hunter_ptr = std::make_unique<SnakeHunter>(grid_width, grid_height);
  PlaceFood();
}

void Game::Run(std::unique_ptr<Controller> &controller_ptr, std::unique_ptr<Renderer> &renderer_ptr,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller_ptr->HandleInput(running, snake_ptr);
    Update();
    renderer_ptr->Render(snake_ptr, snake_hunter_ptr, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer_ptr->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake_ptr->SnakeCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if (!snake_ptr->alive)
    return;

  snake_ptr->Update();

  int new_x = static_cast<int>(snake_ptr->head_x);
  int new_y = static_cast<int>(snake_ptr->head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake_ptr->GrowBody();
    snake_ptr->speed += 0.02;
    snake_hunter_ptr->speed += 0.02;
  }

  snake_hunter_ptr->Update(snake_ptr);
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake_ptr->size; }
std::string Game::GetDeathCause() const
{
  std::string cause_of_death;
  if (snake_ptr->hit_tail == true)
  {
    cause_of_death = "it hit its own tail.";
  };
  if (snake_ptr->hit_wall == true)
  {
    cause_of_death = "it hit the wall.";
  };
  if (snake_ptr->hunted == true)
  {
    cause_of_death = "it was taken by the hunter.";
  };
  return cause_of_death;
}
