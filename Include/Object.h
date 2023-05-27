#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include <string>

using namespace std;

#define ACELERACAO 1

class Object
{
public:
    //Constructor
    Object(int posX, int posY, int height, int width, string shape, int velY);
    
    //Gets
    int getPosX();
    int getPosY();
    int getHeight();
    int getWidth();
    int getVelY();
    string getShape();

    //Sets
    void setPosX(int x);
    void setPosY(int y);
    void setHeight(int height);
    void setWidth(int width);
    void setVelY(int vy);
    void setShape(string shape);

    //Acelerar
    void speedUp();
private:
    int posX, posY, height, width, velY;
    string shape;
};

#endif