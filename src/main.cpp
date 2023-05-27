#include <iostream>
#include "../Include/Game.h"

using namespace std;

//void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip);


int main( int argc, const char** argv )
{
    cout << "Hello, world!\n";
    Game g1 = Game();

    g1.run();

    cout << g1.objects.size();

    return 0;
}




