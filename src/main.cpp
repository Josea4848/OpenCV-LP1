#include <iostream>
#include "../Include/Game.h"
#include "../Include/exibicao.h"
#include <fstream>

using namespace std;
const string baseDir = "../DataBase/base.txt";

//void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip);


int main( int argc, const char** argv ) {
    short int option = 0;
    bool run = true;
    fstream *database = new fstream();
    Game *g1;
    int record = 0;

    //Reading from data
    database->open(baseDir, fstream::in);
    if(database->is_open()) {
        while (true) {
            *database >> record;
            if(database->eof())
                break;
        }
    }
    //Closing file
    database->close();

    g1 = new Game(record);

    g1->run();

    //Saving record
    database->open(baseDir, fstream::out);
    if(database->is_open()) {
        *database << g1->getRecord() << endl;
        database->close();
    }
    

    //Destructors
    delete database;
    delete g1;

    return 0;
}




