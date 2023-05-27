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

using namespace std;
using namespace cv;

const string cascadeName = "../dataset/haarcascade_frontalface_default.xml";

class Game {
public:
    Game();
    
    //Run game
    void run();

    //Screen
    void detectFace(Mat& img, CascadeClassifier& cascade, double scale, bool tryflip);
    void drawMenu(Mat frame);
    int getScreenHeight();
    int getScreenWidth();
    void drawObjects(Mat frame);

    //random methods
    bool newObject();
    int typeObject();
    int xRand();

    //Draw
    void drawTransRect(Mat frame, Scalar color, double alpha, Rect region);
    void drawTransparency(Mat frame, Mat transp, int xPos, int yPos);
    void drawFrame(Mat frame);
    ~Game();
    
    //IsClose
    bool isClose(int x, int y, int x0, int y0);
    bool isCloseOfObjects(int x, int y, vector<Object*> objects);

    vector<Object*> objects;
private:
    int record;
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;
};

#endif