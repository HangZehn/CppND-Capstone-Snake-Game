#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "SDL.h"
#include "snake.h"
#include "snakehunter.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::unique_ptr<Snake> &snake_ptr, std::unique_ptr<SnakeHunter> &snake_hunter_ptr, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
