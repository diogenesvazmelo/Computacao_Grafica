#ifndef DRAWINGS_HPP
#define DRAWINGS_HPP

#include "./colors.hpp"
#if __linux__
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#elif _WIN32
#include <SDL.h>
#include "SDL_opengl.h"
#endif

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
  void desenhaQuadradoIncremento(Coordenada primeira, Coordenada incremento, Color cor);
  void desenhaQuadradoAbs(Coordenada primeira, Coordenada ultima, Color cor);
  void desenhaLinha(Coordenada primeira, Coordenada ultima, Color cor);
  void desenhaTiro(Coordenada primeira,
                   float &COMPRIMENTO_TIRO,
                   float &ALTURA_TIRO,
                   float &COMPRIMENTO_PESON,
                   Color &c);
  void movimentaLateralmente(SDL_Event eventos,
                             float posicao,
                             bool &gEsquerda,
                             bool &gDireita);
  void movimentaLateralmente2(SDL_Event eventos,
                              bool &gTiro,
                              bool &gEsquerda,
                              bool &gDireita);
  void movimentoTiro(Coordenada *tiro, float VELOCIDADE_LATERAL, bool &gTiro);
  void movimentoInimigo(Coordenada *inimigo, Coordenada *incremento, float auxiliar_velocidade_l, int qual_inimigo);
  bool colisaoInimigos(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento);
  bool colisaoTiros(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento);
  Coordenada atira(SDL_Event eventos,
                   Coordenada posicao,
                   Coordenada incremento,
                   bool &gTiro,
                   bool &gEsquerda,
                   bool &gDireita);
} // namespace drws

#endif