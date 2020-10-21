#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

class Blast {
 private:
  float x, y;    // middle of the blast
  float length;  // top of blast is (x,y+length/2)
  float speed;
  float thickness;

 public:
  Blast();
  Blast(float _x, float _y);
  Blast(float _x, float _y, float _length);
  Blast(float _x, float _y, float _length, float _speed);

  float getX();
  void setX(float _x);

  float getY();
  void setY(float _y);

  float getLength();
  void setLength(float _length);

  float getSpeed();
  void setSpeed(float _speed);

  float getThickness();
  void setThickness(float _thickness);

  void moveUp();
  void moveDown();
};

class Spaceship {
 private:
  float x, y;
  float height, width;
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

  float getHeight();
  void setHeight(float _height);

  float getWidth();
  void setWidth(float _width);

  float getSpeed();
  void setSpeed(float _speed);

  bool isDestroyed();
  void setDestroyed(bool _destroyed);

  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();
};

#endif