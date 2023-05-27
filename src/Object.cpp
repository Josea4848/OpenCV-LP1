#include "../Include/Object.h"

Object::Object(int posX, int posY, int height, int width, string shape) {
  setPosX(posX);
  setPosY(posY);
  setHeight(height);
  setWidth(width);
  setShape(shape);
}

//Gets
int Object::getPosX() {return posX;}
int Object::getPosY() {return posY;}
int Object::getHeight() {return height;}
int Object::getWidth() {return width;}
int Object::getVelY() {return velY;}
string Object::getShape() {return shape;}
//Sets
void Object::setPosX(int x) {posX = x;}
void Object::setPosY(int y) {posY = y;}
void Object::setHeight(int height) {this->height = height;}
void Object::setWidth(int width) {this->width = width;}
void Object::setVelY(int vy) {velY = vy;}
void Object::setShape(string shape) {this->shape = shape;}
//SpeedUp
void Object::speedUp() {
  setVelY(getVelY() + ACELERACAO);
}