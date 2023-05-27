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
          drawObjects(frame);
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
      1.05, 2, 0
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
}
void Game::drawMenu(Mat img) {
  // Desenha um texto
  putText	(img, "Placar:", Point(300, 50), FONT_HERSHEY_PLAIN, 2, Scalar(244,0,0)); // fonte
  
  // Desenha quadrados com transparencia
  double alpha = 1;
  drawTransRect(img, Scalar(97, 116, 232), alpha, Rect(  0, getScreenHeight() - getScreenHeight()/8, getScreenWidth(), getScreenHeight()/8)); 
  // Desenha um texto
  putText	(img, "Q para sair", Point(getScreenWidth()/12, getScreenHeight()-getScreenHeight()/22), FONT_HERSHEY_PLAIN, 2, Scalar(121, 200, 224), 3); // fonte
}
void Game::drawObjects(Mat img) {
  int xPos = xRand();

  if(newObject() && objects.size() < 5 && !isCloseOfObjects(xPos, 0, objects)) {
    int objType = typeObject();
    
    if(objType < 6)
      objects.push_back(new Object(xRand(), 0, 50, 50, "../Images/apple.png"));
    else if(objType < 9) 
      objects.push_back(new Object(xRand(), 0, 50, 50, "../Images/apple.png"));
    else 
      objects.push_back(new Object(xRand(), 0, 100, 50, "../Images/poison.png"));
  }
  static int vy = 0;
  for(Object* obj: objects) {
    obj->setPosY(obj->getPosY() + obj->getVelY());
    Mat overlay = imread(obj->getShape(), IMREAD_UNCHANGED);
    resize(overlay, overlay, Size(obj->getHeight(), obj->getWidth()));
    if(overlay.cols + obj->getPosY() < getScreenHeight()- getScreenHeight()/8) {
      drawTransparency(img, overlay, obj->getPosX(), obj->getPosY());
      obj->speedUp();
    }  
  }
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

//Random objects
bool Game::newObject() {
  // Providing a seed value
	srand((unsigned) time(NULL));
  return (rand() % 2);
}
int Game::typeObject() {
  // Providing a seed value
  srand((unsigned) time(NULL));
  /* 
  Retorna um tipo para o objeto
  0 - Maçã
  1 - Maçã podre
  2 - Veneno
  */
  return (rand() % 10);
}
int Game::xRand() {
  int minNumber = getScreenWidth()/14; // Valor mínimo do intervalo
  int maxNumber = getScreenWidth() - getScreenWidth()/14; // Valor máximo do intervalo

  std::random_device rd; // Seed para a geração de números aleatórios
  std::mt19937 gen(rd()); // Gerador de números aleatórios
  std::uniform_int_distribution<int> dis(minNumber, maxNumber); // Distribuição uniforme entre minNumber e maxNumber

  int randomNumber = dis(gen); // Gera um número aleatório dentro do intervalo

  return randomNumber;
}

//isClose
bool Game::isClose(int x, int y, int x0, int y0) {
  int distancia = sqrt(pow(x - x0, 2) + pow(y - y0, 2));
  if (distancia < 400){
    return true;
  } 
  return false;
}
bool Game::isCloseOfObjects(int x, int y, vector<Object*> objects) {
  for(Object* obj: objects) {
    if(isClose(x, y, obj->getPosX(), obj->getPosY())) {
      return true;
    }
  }

  return false;
}

Game::~Game()
{

}