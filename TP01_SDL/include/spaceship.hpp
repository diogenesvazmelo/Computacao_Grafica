#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SDL2/SDL.h>

class Blast {
 private:
  SDL_Rect rect;
  float speed;

 public:
  Blast();
  Blast(float _x, float _y);
  Blast(float _x, float _y, float _length);
  Blast(float _x, float _y, float _length, float _speed);

  float getX();
  void setX(float _x);

  float getY();
  void setY(float _y);

  SDL_Rect* getRect();

  float getLength();
  void setLength(float _length);

  float getThickness();
  void setThickness(float _thickness);

  float getSpeed();
  void setSpeed(float _speed);

  void moveUp(float tConst);
  void moveDown(float tConst);
};

class Spaceship {
 private:
  SDL_Rect rect;
  float speed;
  bool destroyed;

 public:
  Spaceship();
  Spaceship(float _x, float _y);
  Spaceship(float _x, float _y, float _height, float _width);
  Spaceship(float _x, float _y, float _speed);
  Spaceship(float _x, float _y, float _height, float _width, float _speed);

  float getX();
  void setX(float _x);

  float getY();
  void setY(float _y);

  SDL_Rect* getRect();

  float getHeight();
  void setHeight(float _height);

  float getWidth();
  void setWidth(float _width);

  float getSpeed();
  void setSpeed(float _speed);

  bool isDestroyed();
  void setDestroyed(bool _destroyed);

  void moveLeft(float tConst);
  void moveRight(float tConst);
  void moveDown(float tConst);
  void moveUp(float tConst);
};

#endif