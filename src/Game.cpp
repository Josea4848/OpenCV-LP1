#include "../Include/Game.h"

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

  //Seta estado inicial do jogo
  setMainMenu(true);

  //Variável de controle em caso de perder o jogo
  setGameOver(false);

  //Detecta webcam e inseri a tela
  webCamScreen();

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
      string path;
      switch (typeObject) {
      case 0:
        placar++;
        // Desenha um texto
        putText	(frame, "Placar: " + to_string(placar), Point(getScreenWidth()/12, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0),3); // fonte
        path = "../Sound/siu.wav";
        break;
      case 1:
        if(placar > 0) {
          placar--;
          putText	(frame, "Placar: " + to_string(placar), Point(getScreenWidth()/12, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,255), 3); // fonte
          path = "../Sound/oof.wav";
        }
        break;
      case 2:
        setGameOver(true);
        path = "../Sound/vaiprovasco.wav";
        break;
      default:
        break;
      }
      playSoundInBackground(path);
      
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

//MainMenu
bool Game::isMainMenu(){return mainMenu;}
void Game::setMainMenu(bool value) {mainMenu = value;}

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
    throw new InvalidDificultyValue();
    break;
  }
}

//Exibe pontuacao
void Game::exibePontuacao() {
  cout << "=======================================\n";
  cout << "\tSua pontuação: " << getPlacar() << endl;
  cout << "=======================================\n";
}

//Check menu
void Game::checkMenu() {
  if(distancePoints(getFaceX(), getFaceY(),getScreenWidth()/2, getScreenHeight()/2) < 25)
    setMainMenu(false);
}

//Destructor
Game::~Game() {
  for(Object *obj: objects) {
    delete obj;
  }
}