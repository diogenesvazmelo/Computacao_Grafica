#include "../include/drawings.hpp"

using namespace drws;

void drws::desenhaQuadradoIncremento(Spaceship sp, Color cor)
{
  glColor3f(cor.r, cor.g, cor.b);
  // Desenha um pol�gono por seus v�rtices

  float points[4] = {
      sp.getX() - sp.getWidth() / 2,
      sp.getX() + sp.getWidth() / 2,
      sp.getY() - sp.getHeight() / 2,
      sp.getY() + sp.getHeight() / 2,
  };
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(points[0], points[2], 0.0);
  glVertex3f(points[1], points[2], 0.0);
  glVertex3f(points[1], points[3], 0.0);
  glVertex3f(points[0], points[3], 0.0);

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
