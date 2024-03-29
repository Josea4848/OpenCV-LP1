#ifndef GAME_H
#define GAME_H

#pragma once

#include <iostream>
#include <vector>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "Object.h"
#include <random>
#include <cmath>
#include "../Exceptions/InvalidDificultyValue.h"
#include <unistd.h>
#include "sound.h"

using namespace std;
using namespace cv;

const string cascadeName = "../dataset/haarcascade_frontalface_default.xml";

class Game {
public:
    //Constructors
    Game();
    Game(int record);
    
    //Run game
    void run();

    //Screen
    void webCamScreen();
    void detectFace(Mat& img, CascadeClassifier& cascade, double scale, bool tryflip);
    void drawMenu(Mat frame);
    void drawMainMenu(Mat frame);
    int getScreenHeight();
    int getScreenWidth();
    void drawObjects(Mat frame);
    void drawTransRect(Mat frame, Scalar color, double alpha, Rect region);
    void drawTransparency(Mat frame, Mat transp, int xPos, int yPos);
    void drawFrame(Mat frame);

    //random methods
    bool newObject();
    int typeObject();
    int xRand();

    //Destructor
    ~Game();

    //Face position
    int getFaceX();
    int getFaceY();
    void setFaceX(int x, int faceWidth);
    void setFaceY(int y, int faceHeight);

    //IsClose
    bool isClose(int x, int y, int x0, int y0);
    bool isCloseOfObjects(int x, int y, vector<Object*> objects);

    //check 
    void checkColision();
    void checkMenu();

    //Distance points
    int distancePoints(int x, int y, int x0, int y0);

    //Record
    int getRecord();
    void setRecord(int record);

    //GameOver
    bool isGameOver();
    void setGameOver(bool state);

    //MainMenu
    bool isMainMenu();
    void setMainMenu(bool valeu);

    //Placar
    int getPlacar();
    void setPlacar(int placar);

    //changeDificulty
    void changeDificulty(int dificulty);

    //Aceleracao
    int getAcel();
    void setAcel(int acel);

    //Exibe pontuação
    void exibePontuacao();

private:
    vector<Object*> objects;
    int record, placar = 0, dificulty = 0;
    VideoCapture capture;
    Mat frame;
    bool tryflip, gameOver;
    CascadeClassifier cascade;
    double scale;
    int faceX, faceY;
    int acel;
    bool mainMenu;
};

#endif