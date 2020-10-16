#include "../include/drawings.hpp"

using namespace drws;

void drws::resetScreen(int width, int height)
{
  /// RENDERIZACAO
  glClear(GL_COLOR_BUFFER_BIT); //Limpa o buffer
  // Inicia matriz
  glPushMatrix();
  // Dimensoes da Matriz
  glOrtho(0, width, height, 0, -1, 1);
}

void drws::drawsSpaceship(Spaceship sp, Color c)
{
  glColor3f(c.r, c.g, c.b);
  // Desenha um poligono por seus v�rtices

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

  glColor3f(c.r, c.g, c.b);

  // Desenha um poligono por seus vertices
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(primeira.x, primeira.y, 0.0);
  glVertex3f(primeira.x + incremento.x, primeira.y, 0.0);
  glVertex3f(primeira.x + incremento.x, primeira.y + incremento.y, 0.0);
  glVertex3f(primeira.x, primeira.y + incremento.y, 0.0);
  glEnd();
}

void drws::drawsBlast(Blast b, Color c)
{
  glColor3f(c.r, c.g, c.b);
  float thickness = 20.0;
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(b.getX() - thickness / 2, b.getY() - b.getLength() / 2, 0.0);
  glVertex3f(b.getX() + thickness / 2, b.getY() - b.getLength() / 2, 0.0);
  glVertex3f(b.getX() - thickness / 2, b.getY() + b.getLength() / 2, 0.0);
  glVertex3f(b.getX() + thickness / 2, b.getY() + b.getLength() / 2, 0.0);
  glEnd();
}
