#ifndef GAME_H
#define GAME_H

#pragma once

#include <iostream>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "Object.h"

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

    //Draw
    void drawTransRect(Mat frame, Scalar color, double alpha, Rect region);
    void drawTransparency(Mat frame, Mat transp, int xPos, int yPos);
    void drawFrame(Mat frame);
    ~Game();

private:
    int record;
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;
};

#endif