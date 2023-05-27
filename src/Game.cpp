#include "../Include/Game.h"

/**
 * @brief Draws a transparent image over a frame Mat.
 * 
 * @param frame the frame where the transparent image will be drawn
 * @param transp the Mat image with transparency, read from a PNG image, with the IMREAD_UNCHANGED flag
 * @param xPos x position of the frame image where the image will start.
 * @param yPos y position of the frame image where the image will start.
 */


/**
 * @brief Draws a transparent rect over a frame Mat.
 * 
 * @param frame the frame where the transparent image will be drawn
 * @param color the color of the rect
 * @param alpha transparence level. 0 is 100% transparent, 1 is opaque.
 * @param regin rect region where the should be positioned
 */

Game::Game() {

}

//Run
void Game::run() {
  scale = 1; // usar 1, 2, 4.
  if (scale < 1)
      scale = 1;
  tryflip = true;

  //Tentando abrir o cascade
  if (!cascade.load(cascadeName)) {
      cerr << "ERROR: Could not load classifier cascade" << endl;
  }

  //Tentando abrir webcam
  if(!capture.open(0))
  {
      cout << "Capture from camera #0 didn't work" << endl;
  }

  if( capture.isOpened() ) {
      cout << "Video capturing has been started ..." << endl;

      while (true)
      {
          capture >> frame;
          if( frame.empty() )
              break;
          detectFace( frame, cascade, scale, tryflip );
          drawMenu(frame);
          drawFrame(frame);

          char c = (char)waitKey(10);
          //Encerra aplicação
          if( c == 27 || c == 'q' || c == 'Q' )
              break;
      }
  }
}

//Detect face and draw frame 
void Game::detectFace( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip)
{
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    Scalar color = Scalar(255,0,0);

    if( tryflip )
        flip(img, img, 1);

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    if (scale > 1)
        resize( img, img, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    t = (double)getTickCount();

    cascade.detectMultiScale( smallImg, faces,
        1.3, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(40, 40) );
    t = (double)getTickCount() - t;
    printf( "detection time = %g ms\n", t*1000/getTickFrequency());

    int largestArea = 0;
    Rect r;
    // Percorre as faces encontradas, e retorna o índice da maior face
    for ( size_t i = 0; i < faces.size(); i++ ) {
      int currentArea = faces[i].width*faces[i].height;
      if(currentArea > largestArea) {
        largestArea = currentArea;
        r = faces[i];
      }
    }

    rectangle( img, Point(cvRound(r.x), cvRound(r.y)),
                    Point(cvRound((r.x + r.width-1)), cvRound((r.y + r.height-1))),
                    color, 3); 

    // Desenha uma imagem
    Mat overlay = cv::imread("../Images/apple.png", IMREAD_UNCHANGED);
    //drawTransparency(img, overlay, 10, 250);

    // Desenha um texto
    color = Scalar(0,0,255);
    putText	(img, "Placar:", Point(300, 50), FONT_HERSHEY_PLAIN, 2, color); // fonte
}
void Game::drawMenu(Mat img) {
  // Desenha quadrados com transparencia
  double alpha = 0.3;
  drawTransRect(img, Scalar(0,255,0), alpha, Rect(  0, 0, 200, 200));
  drawTransRect(img, Scalar(255,0,0), alpha, Rect(200, 0, 200, 200));
}
void Game::drawFrame(Mat img) {
  // Desenha o frame na tela
  imshow( "Fruit tinta", img );
}
//Height
int Game::getScreenHeight() {
  return capture.get(cv::CAP_PROP_FRAME_HEIGHT);
}
//Width
int Game::getScreenWidth() {
  return capture.get(cv::CAP_PROP_FRAME_WIDTH);
}

//Draw
void Game::drawTransRect(Mat frame, Scalar color, double alpha, Rect region) {
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color); 
    addWeighted(rectImg, alpha, roi, 1.0 - alpha , 0, roi); 
}
void Game::drawTransparency(Mat frame, Mat transp, int xPos, int yPos) {
    Mat mask;
    vector<Mat> layers;

    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png's alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

Game::~Game()
{

}