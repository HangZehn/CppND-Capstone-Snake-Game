#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>

class Controller
{
public:
  Controller(){};
  ~Controller(){};
  void HandleInput(bool &running, std::unique_ptr<Snake> &snake_ptr) const;

private:
  void ChangeDirection(std::unique_ptr<Snake> &snake_ptr, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
