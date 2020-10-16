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

void drws::drawsBlast(Blast b, Color c)
{
  glColor3f(c.r, c.g, c.b);
  // std::cout << b.getThickness() << std::endl;
  // float thickness = 10.0;

  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(b.getX() - b.getThickness() / 2, b.getY() - b.getLength() / 2, 0.0);
  glVertex3f(b.getX() + b.getThickness() / 2, b.getY() - b.getLength() / 2, 0.0);
  glVertex3f(b.getX() - b.getThickness() / 2, b.getY() + b.getLength() / 2, 0.0);
  glVertex3f(b.getX() + b.getThickness() / 2, b.getY() + b.getLength() / 2, 0.0);
  glEnd();
}
