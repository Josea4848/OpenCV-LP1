#include "../Include/Game.h"

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
      1.8, 2, 0
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

  //Definindo coordenada X atual
  setFaceX(r.x, r.width);
  //Definindo coordenada Y atual
  setFaceY(r.y, r.height);

  rectangle( img, Point(cvRound(r.x), cvRound(r.y)),
                  Point(cvRound((r.x + r.width-1)), cvRound((r.y + r.height-1))),
                  color, 3);  
}
void Game::drawMenu(Mat img) {
  // Desenha um texto
  putText	(img, "Placar: " + to_string(placar), Point(getScreenWidth()/12, 50), FONT_HERSHEY_PLAIN, 2, Scalar(244,0,0), 3); // fonte
  
  // Desenha quadrados com transparencia
  double alpha = 1;
  drawTransRect(img, Scalar(97, 116, 232), alpha, Rect(  0, getScreenHeight() - getScreenHeight()/8, getScreenWidth(), getScreenHeight()/8)); 
  // Desenha um texto
  putText	(img, "Q para sair", Point(getScreenWidth()/12, getScreenHeight()-getScreenHeight()/22), FONT_HERSHEY_PLAIN, 2, Scalar(121, 200, 224), 3); // fonte

  // Desenha troféu
  Mat trophy = imread("../Images/trophy.png", IMREAD_UNCHANGED);
  double proporcao = min((double)(getScreenWidth()/30)/trophy.cols, (double)(getScreenHeight()/20)/trophy.rows);
  resize(trophy, trophy, Size(getScreenWidth()*proporcao, getScreenHeight()*proporcao));
  drawTransparency(img, trophy, getScreenWidth() - getScreenWidth()/4, getScreenHeight()/22);
  putText	(img, to_string(getRecord()), Point(getScreenWidth()-getScreenWidth()/4 + 50, getScreenHeight()/12), FONT_HERSHEY_PLAIN, 2, Scalar(121, 200, 224), 3); // fonte
}
void Game::drawObjects(Mat img) {
  int xPos = xRand();

  if(newObject() && objects.size() < 5 && !isCloseOfObjects(xPos, 0, objects)) {
    int objType = typeObject();
    
    if(objType < 6)
      objects.push_back(new Object(0, xRand(), 0, 50, 50, "../Images/apple.png", 0, getAcel()));
    else if(objType < 9) 
      objects.push_back(new Object(1, xRand(), 0, 50, 50, "../Images/rottenapple.png", 0, getAcel()));
    else 
      objects.push_back(new Object(2, xRand(), 0, 50, 50, "../Images/poison.png", 0, getAcel()));
  }
  
  vector<int> objectsToDel;

  //Percorre todos os objetos do vector
  for(int i = 0; i < objects.size(); i++) {
    objects[i]->setPosY(objects[i]->getPosY() + objects[i]->getVelY());
    Mat overlay = imread(objects[i]->getShape(), IMREAD_UNCHANGED);
    resize(overlay, overlay, Size(objects[i]->getHeight(), objects[i]->getWidth()));
    //Se o objeto ainda não passar do limite, será exibido
    if(overlay.cols + objects[i]->getPosY() /* + objects[i]->getVelY() */ < getScreenHeight()- getScreenHeight()/8) {
      drawTransparency(img, overlay, objects[i]->getPosX(), objects[i]->getPosY());
      objects[i]->speedUp();
    }
    //Caso tenha passado do limite, irá ter seu índice salvo, para deletar
    else {
      objectsToDel.push_back(i);
    }  
  }

  for(int index: objectsToDel) {
    objects.erase(objects.begin() + index);
  } 

}
void Game::drawFrame(Mat img) {
  // Desenha o frame na tela
  imshow( "Fruit Tinta", img);
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