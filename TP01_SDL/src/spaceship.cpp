#include "../include/spaceship.hpp"
#include <cstddef>

const float DEFAULT_BLAST_LENGTH = 10.0;
const float DEFAULT_BLAST_SPEED = 2.0;

// BLAST SECTION

Blast::Blast()
{
  x = y = length = speed = 0.0;
}
Blast::Blast(float _x, float _y)
{
  x = _x;
  y = _y;
  length = DEFAULT_BLAST_LENGTH;
  speed = DEFAULT_BLAST_SPEED;
}
Blast::Blast(float _x, float _y, float _length)
{
  x = _x;
  y = _y;
  length = _length;
  speed = DEFAULT_BLAST_SPEED;
}
Blast::Blast(float _x, float _y, float _length, float _speed)
{
  x = _x;
  y = _y;
  length = _length;
  speed = _speed;
}

float Blast::getX()
{
  return x;
}
void Blast::setX(float _x)
{
  x = _x;
}
float Blast::getY()
{
  return y;
}
void Blast::setY(float _y)
{
  y = _y;
}

float Blast::getLength()
{
  return length;
}
void Blast::setLength(float _length)
{
  length = _length;
}

float Blast::getSpeed()
{
  return speed;
}
void Blast::setSpeed(float _speed)
{
  speed = _speed;
}

void Blast::moveUp()
{
  y -= speed;
}
void Blast::moveDown()
{
  y += speed;
}

// BLAST FINISHED
const float DEFAULT_SPACESHIP_SPEED = 1.0;
const float DEFAULT_SPACESHIP_HEIGHT = 50.0;
const float DEFAULT_SPACESHIP_WIDTH = 50.0;

Spaceship::Spaceship()
{
  x = y = speed = height = width = 0.0;
  b = NULL;
  destroyed = false;
}
Spaceship::Spaceship(float _x, float _y)
{
  x = _x;
  y = _y;
  height = DEFAULT_SPACESHIP_HEIGHT;
  width = DEFAULT_SPACESHIP_WIDTH;
  speed = DEFAULT_SPACESHIP_SPEED;
  b = NULL;
}
Spaceship::Spaceship(float _x, float _y, float _height, float _width)
{
  x = _x;
  y = _y;
  height = _height;
  width = _width;
  speed = DEFAULT_SPACESHIP_SPEED;
  b = NULL;
}
Spaceship::Spaceship(float _x, float _y, float _speed)
{
  x = _x;
  y = _y;
  height = DEFAULT_SPACESHIP_HEIGHT;
  width = DEFAULT_SPACESHIP_WIDTH;
  speed = _speed;
  b = NULL;
}
Spaceship::Spaceship(float _x, float _y, float _height, float _width, float _speed)
{
  x = _x;
  y = _y;
  height = _height;
  width = _width;
  speed = _speed;
  b = NULL;
}

float Spaceship::getX()
{
  return x;
}
void Spaceship::setX(float _x)
{
  x = _x;
}

float Spaceship::getY()
{
  return y;
}
void Spaceship::setY(float _y)
{
  y = _y;
}

float Spaceship::getHeight()
{
  return height;
}
void Spaceship::setHeight(float _height)
{
  height = _height;
}

float Spaceship::getWidth()
{
  return width;
}
void Spaceship::setWidth(float _width)
{
  width = _width;
}

float Spaceship::getSpeed()
{
  return speed;
}
void Spaceship::setSpeed(float _speed)
{
  speed = _speed;
}

bool Spaceship::blastExists()
{
  return (b == NULL) ? false : true;
}
Blast *Spaceship::getBlast()
{
  return b;
}
// TODO: implements firing shot !
void Spaceship::fireBlast()
{
  if (b == NULL)
  {
    Blast blast = Blast(x, y - height);
    b = &blast;
  }
}

bool Spaceship::isDestroyed()
{
  return destroyed;
}
void Spaceship::setDestroyed(bool _destroyed)
{
  destroyed = _destroyed;
}

void Spaceship::moveLeft()
{
  x -= speed;
}
void Spaceship::moveRight()
{
  x += speed;
}
void Spaceship::moveDown()
{
  y += speed / 4;
}
void Spaceship::moveUp()
{
  y -= speed / 4;
}

//TODO: maybe remove blast from inside the spaceship?