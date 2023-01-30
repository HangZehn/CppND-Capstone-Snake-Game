#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "snakehunter.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game(){};
  // void Run(Controller const &controller, Renderer &renderer,
  //          std::size_t target_frame_duration);
  void Run(std::unique_ptr<Controller> &controller_ptr, std::unique_ptr<Renderer> &renderer_ptr,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::string GetDeathCause() const;

private:
  std::unique_ptr<Snake> snake_ptr;
  std::unique_ptr<SnakeHunter> snake_hunter_ptr;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif
