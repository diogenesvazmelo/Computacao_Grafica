#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

class Blast
{
private:
  float x, y;   // middle of the blast
  float length; // top of blast is (x,y+length/2)
  float speed;

public:
  Blast();
  Blast(float _x, float _y);
  Blast(float _x, float _y, float _length);
  Blast(float _x, float _y, float _length, float _speed);

  float getLength();
  void setLength(float _length);

  float getSpeed();
  void setSpeed(float _speed);

  void moveUp();
  void moveDown();
};

class Spaceship
{
private:
  float x, y;
  float speed;
  Blast *b; // only one fire per ship
  bool destroyed;

public:
  Spaceship();
  Spaceship(float _x, float _y);
  Spaceship(float _x, float _y, float _speed);

  float getX();
  void setX(float _x);

  float getY();
  void setY(float _y);

  float getSpeed();
  void setSpeed(float _speed);

  Blast getBlast();
  void fireBlast();

  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();
};

#endif