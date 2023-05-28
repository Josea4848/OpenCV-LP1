#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include <string>

using namespace std;
class Object
{
public:
    //Constructor
    Object(int type, int posX, int posY, int height, int width, string shape, int velY, int acelY);
    
    //Gets
    int getType();
    int getPosX();
    int getPosY();
    int getHeight();
    int getWidth();
    int getVelY();
    int getAcelY();
    string getShape();

    //Sets
    void setType(int type);
    void setPosX(int x);
    void setPosY(int y);
    void setHeight(int height);
    void setWidth(int width);
    void setVelY(int vy);
    void setShape(string shape);
    void setAcelY(int acelY);

    //Acelerar
    void speedUp();
private:
    int posX, posY, height, width, velY, acelY;
    string shape;
    int type;
};

#endif