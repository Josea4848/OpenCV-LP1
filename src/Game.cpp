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

Game::Game() : Game(0) {}
Game::Game(int record) {
  setRecord(record);
  setAcel(2);
}

//Run
void Game::run() {
  scale = 1; // usar 1, 2, 4.
  if (scale < 1)
    scale = 1;
  tryflip = true;


  //Placar inicial
  setPlacar(0);

  //Variável de controle em caso de perder o jogo
  setGameOver(false);

  //Tentando abrir o cascade
  if (!cascade.load(cascadeName)) {
    cerr << "ERROR: Could not load classifier cascade" << endl;
  }

  cout << "TENTA\n";

  //Tentando abrir webcam
  if(!capture.open(1)) {
    cout << "Capture from camera #0 didn't work" << endl;
  }

  cout << "HHAHA\n";

  if( capture.isOpened() ) {
    cout << "Video capturing has been started ..." << endl;
    namedWindow("Fruit Tinta", WINDOW_NORMAL);
    while (true) {
      capture >> frame;
      if( frame.empty() )
          break;
      detectFace( frame, cascade, scale, tryflip );
      drawObjects(frame);
      drawMenu(frame);
      checkColision();
      drawFrame(frame);

      char c = (char)waitKey(10);
      //Encerra aplicação
      if( c == 27 || c == 'q' || c == 'Q' || isGameOver()) {
        destroyAllWindows();
        break;
      }
          
    }
  }
  //Caso o placar seja o novo record
  if (getPlacar() > getRecord()) {
    setRecord(getPlacar());
  }
  
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
  int minNumber = getScreenWidth()/4; // Valor mínimo do intervalo
  int maxNumber = getScreenWidth() - getScreenWidth()/4; // Valor máximo do intervalo

  std::random_device rd; // Seed para a geração de números aleatórios
  std::mt19937 gen(rd()); // Gerador de números aleatórios
  std::uniform_int_distribution<int> dis(minNumber, maxNumber); // Distribuição uniforme entre minNumber e maxNumber

  int randomNumber = dis(gen); // Gera um número aleatório dentro do intervalo

  return randomNumber;
}

//isClose
bool Game::isClose(int x, int y, int x0, int y0) {
  int distancia = sqrt(pow(x - x0, 2) + pow(y - y0, 2));
  if (distancia < 200){
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

//Check Colision
void Game::checkColision() {
  for(int i = 0; i < objects.size(); i++) {
    if(distancePoints(getFaceX(), getFaceY(), objects[i]->getPosX(), objects[i]->getPosY()) < 100) {
      int typeObject = objects[i]->getType();
      switch (typeObject) {
      case 0:
        placar++;
        // Desenha um texto
        putText	(frame, "Placar: " + to_string(placar), Point(getScreenWidth()/12, 50), FONT_HERSHEY_PLAIN, 2, Scalar(244,255,0),3); // fonte
        break;
      case 1:
        if(placar > 0) {
          placar--;
          putText	(frame, "Placar: " + to_string(placar), Point(getScreenWidth()/12, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,255), 3); // fonte
        }
        break;
      case 2:
        setGameOver(true);
        break;
      default:
        break;
      }
      objects.erase(objects.begin() + i);
      break;
    }
  }
}

//Distance point
int Game::distancePoints(int x, int y, int x0, int y0) {
  return sqrt(pow(x - x0, 2)+ pow(y - y0, 2));
}

//Face position
int Game::getFaceX() { return faceX; }
int Game::getFaceY() { return faceY; }
void Game::setFaceX(int x, int faceWidth) {
  faceX = x + faceWidth/2;
}
void Game::setFaceY(int y, int faceHeight) {
  faceY = y + faceHeight/2;
}

//Record
int Game::getRecord() {return record;}
void Game::setRecord(int record) {this->record = record;}

//Placar
int Game::getPlacar() {return placar;}
void Game::setPlacar(int placar) {this->placar=placar;}

//GameOver
bool Game::isGameOver() {return gameOver;}
void Game::setGameOver(bool state) {
  gameOver = state;
}

//acel
int Game::getAcel() {return acel;}
void Game::setAcel(int acel) {this->acel = acel;}

//change dificulty
void Game::changeDificulty(int dificulty) {
  switch (dificulty) {
  case 1: //Fácil
    setAcel(1);
    break;
  case 2: //Intermediário
    setAcel(3);
    break;
  case 3: //Difícil
    setAcel(10);
    break;
  case 4: //Impossível
    setAcel(30);
    break;
  default:
    cout << InvalidDificultyValue().what() << endl;
    sleep(2);
    break;
  }
}

//Destructor
Game::~Game() {
  for(Object *obj: objects) {
    delete obj;
  }
}