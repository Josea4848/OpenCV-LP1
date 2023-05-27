#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include <string>

using namespace std;

class Object
{
public:
    //Constructor
    Object(int posX, int posY, int height, int width, string shape);
    
    //Gets
    int getPosX();
    int getPosY();
    int getHeight();
    int getWidth();
    string getShape();

    //Sets
    void setPosX(int x);
    void setPosY(int y);
    void setHeight(int height);
    void setWidth(int width);
    void setShape(string shape);
private:
    int posX, posY, height, width;
    string shape;
};

#endif