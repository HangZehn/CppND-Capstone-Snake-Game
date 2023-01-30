#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::unique_ptr<Renderer> renderer_ptr = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  std::unique_ptr<Controller> controller_ptr = std::make_unique<Controller>();

  std::unique_ptr<Game> game_ptr = std::make_unique<Game>(kGridWidth, kGridHeight);
  game_ptr->Run(controller_ptr, renderer_ptr, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "The snake died because " << game_ptr->GetDeathCause() << "\n";
  std::cout << "Score: " << game_ptr->GetScore() << "\n";
  std::cout << "Size: " << game_ptr->GetSize() << "\n";
  return 0;
}
