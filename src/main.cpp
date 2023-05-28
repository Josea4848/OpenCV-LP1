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

    while (run) {
        exibeMenu();
        //Lê opção
        cout << "\nSua opção: ";
        cin >> option;

        //Clear terminal
        clearTerminal();
        switch (option) {
        case 1:
            g1->run();
            //clear terminal
            clearTerminal();
            g1->exibePontuacao();
            sleep(3);
            break;
        case 2:
            short int dificulty;
            menuDificuldade();
            cout << "Sua opção: ";
            cin >> dificulty;
            try {
                g1->changeDificulty(dificulty);
            }
            catch(InvalidDificultyValue *e) {
                cout << e->what() << '\n';
                sleep(2);
                delete e;
            }
            break;
        case 3:
            run = false;
            break;
        default:
            cout << "Opção Inválida\n";
            break;
        }
    
        clearTerminal();
    }

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




