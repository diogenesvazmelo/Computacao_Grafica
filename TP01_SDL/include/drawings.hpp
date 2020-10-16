#ifndef DRAWINGS_HPP
#define DRAWINGS_HPP

#include "./colors.hpp"
#if __linux__
#include "SDL/SDL_opengl.h"
#elif _WIN32
#include "SDL_opengl.h"
#endif

#include "../include/spaceship.hpp"
#include <iostream>

struct Coordenada
{
  float x;
  float y;
};

struct Inimigo
{
  Coordenada inicial;
  Coordenada incremento;
  bool vivo;
};

namespace drws
{
  void resetScreen(int width, int height);
  void drawsSpaceship(Spaceship sp, Color cor);
  void drawsBlast(Blast b, Color c);
} // namespace drws

#endif