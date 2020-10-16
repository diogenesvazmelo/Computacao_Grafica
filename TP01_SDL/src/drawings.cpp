#include "../include/drawings.hpp"

using namespace drws;

void drws::desenhaQuadradoIncremento(Coordenada primeira, Coordenada incremento, Color cor)
{
  glColor3f(cor.r, cor.g, cor.b);
  // Desenha um pol�gono por seus v�rtices

  glBegin(GL_TRIANGLE_FAN);
  // NOVIDADE: antes os valores eram -0.5, 0.5
  glVertex3f(primeira.x, primeira.y, 0.0);
  glVertex3f(primeira.x + incremento.x, primeira.y, 0.0);
  glVertex3f(primeira.x + incremento.x, primeira.y + incremento.y, 0.0);
  glVertex3f(primeira.x, primeira.y + incremento.y, 0.0);
  glEnd();
}

void drws::desenhaQuadradoAbs(Coordenada primeira, Coordenada ultima, Color cor)
{
  glColor3f(cor.r, cor.g, cor.b);
  // Desenha um pol�gono por seus v�rtices

  glBegin(GL_TRIANGLE_FAN);
  // NOVIDADE: antes os valores eram -0.5, 0.5
  glVertex3f(primeira.x, primeira.y, 0.0);
  glVertex3f(ultima.x, primeira.y, 0.0);
  glVertex3f(ultima.x, ultima.y, 0.0);
  glVertex3f(primeira.x, ultima.y, 0.0);
  glEnd();
}

void drws::desenhaLinha(Coordenada primeira, Coordenada ultima, Color cor)
{
  glColor3f(cor.r, cor.g, cor.b);
  // Desenha um poligono por seus vertices

  glBegin(GL_LINES); // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGOM
  glVertex3f(primeira.x, primeira.y, 0.0);
  glVertex3f(ultima.x, ultima.y, 0.0);
  glEnd();
}

void drws::desenhaTiro(Coordenada primeira,
                       float &COMPRIMENTO_TIRO,
                       float &ALTURA_TIRO,
                       float &COMPRIMENTO_PERSON,
                       Color &c)
{
  Coordenada incremento;
  incremento.x = COMPRIMENTO_TIRO;
  incremento.y = ALTURA_TIRO;

  primeira.x += (COMPRIMENTO_PERSON / 2) - (incremento.x / 2);

  Color cor = c;
  glColor3f(cor.r, cor.g, cor.b);

  // Desenha um pol�gono por seus v�rtices

  glBegin(GL_TRIANGLE_FAN);
  // NOVIDADE: antes os valores eram -0.5, 0.5
  glVertex3f(primeira.x, primeira.y, 0.0);
  glVertex3f(primeira.x + incremento.x, primeira.y, 0.0);
  glVertex3f(primeira.x + incremento.x, primeira.y + incremento.y, 0.0);
  glVertex3f(primeira.x, primeira.y + incremento.y, 0.0);
  glEnd();
}

void drws::movimentaLateralmente(SDL_Event eventos,
                                 float posicao,
                                 bool &gEsquerda,
                                 bool &gDireita)
{
  //if (posicao <= 0)
  {
      //gEsquerda == false;
  }
  //else if (posicao >= LARGURA_JANELA)
  {
      //gDireita == false;
  }
  //else
  {
    if (eventos.type == SDL_KEYDOWN)
    {
      if (eventos.key.keysym.sym == SDLK_LEFT && eventos.key.keysym.sym == SDLK_RIGHT)
      {
        gEsquerda = false;
        gDireita = false;
      }
      else if (eventos.key.keysym.sym == SDLK_LEFT)
      {
        gEsquerda = true;
      }
      else if (eventos.key.keysym.sym == SDLK_RIGHT)
      {
        gDireita = true;
      }
    }
    else if (eventos.type == SDL_KEYUP)
    {
      if (eventos.key.keysym.sym == SDLK_LEFT)
      {
        gEsquerda = false;
      }
      if (eventos.key.keysym.sym == SDLK_RIGHT)
      {
        gDireita = false;
      }
    }
  }
}

void drws::movimentaLateralmente2(SDL_Event eventos,
                                  bool &gTiro,
                                  bool &gEsquerda,
                                  bool &gDireita)
{
  if (eventos.type == SDL_KEYDOWN)
  {
    //if (eventos.key.keysym.sym == SDLK_LEFT && eventos.key.keysym.sym == SDLK_RIGHT)
    //{
    //    gEsquerda = false;
    //    gDireita = false;
    //}
    if (eventos.key.keysym.sym == SDLK_LEFT)
    {
      gEsquerda = true;
    }
    else if (eventos.key.keysym.sym == SDLK_RIGHT)
    {
      gDireita = true;
    }
  }
  else if (eventos.type == SDL_KEYUP)
  {
    if (eventos.key.keysym.sym == SDLK_LEFT)
    {
      gEsquerda = false;
    }
    if (eventos.key.keysym.sym == SDLK_RIGHT)
    {
      gDireita = false;
    }
  }
}

void drws::movimentoTiro(Coordenada *tiro, float VELOCIDADE_LATERAL, bool &gTiro)
{
  tiro->y += (VELOCIDADE_LATERAL * (-1));

  if (tiro->y < 0)
  {
    gTiro = false;
  }
}

void drws::movimentoInimigo(Coordenada *inimigo, Coordenada *incremento, float auxiliar_velocidade_l, int qual_inimigo)
{
  inimigo->x += auxiliar_velocidade_l;
}

bool drws::colisaoInimigos(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento)
{
  if (obj1.y + obj1_incremento.y < obj2.y)
  {
    return false;
  }
  else if (obj1.y > obj2.y + obj2_incremento.y)
  {
    return false;
  }
  else if (obj1.x + obj1_incremento.x < obj2.x)
  {
    return false;
  }
  else if (obj1.x > obj2.x + obj2_incremento.x)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool drws::colisaoTiros(Coordenada obj1, Coordenada obj1_incremento, Coordenada obj2, Coordenada obj2_incremento)
{
  if (obj1.y + obj1_incremento.y < obj2.y)
  {
    return false;
  }
  else if (obj1.y > obj2.y + obj2_incremento.y)
  {
    return false;
  }
  else if (obj1.x + obj1_incremento.x < obj2.x)
  {
    return false;
  }
  else if (obj1.x > obj2.x + obj2_incremento.x)
  {
    return false;
  }
  else
  {
    return true;
  }
}

Coordenada drws::atira(SDL_Event eventos,
                       Coordenada posicao,
                       Coordenada incremento,
                       bool &gTiro,
                       bool &gEsquerda,
                       bool &gDireita)
{
  //    if (eventos.type == SDL_KEYDOWN)
  //    {
  //        if (eventos.key.keysym.sym == SDLK_SPACE)
  //        {
  //            gTiro = true;
  //            posicao.y -= incremento.y + 5;
  //
  //            return (posicao);
  //        }
  //    }
  if (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_SPACE)
  {
    gTiro = true;
    posicao.y -= incremento.y + 5;

    return (posicao);
  }
  else
  {
    Coordenada origem;
    origem.x = 0;
    origem.y = 0;

    return origem;
  }
}