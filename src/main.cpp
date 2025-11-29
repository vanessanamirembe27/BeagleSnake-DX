#include <QApplication> 
//#include "gamewindow.h" add back once implemented pause screen/ title screen 
#include "gameview.h"

int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv); 

    GameView view; //starts game instance

    view.showFullScreen(); //want full screen on LCD Cape 

    return a.exec(); 
}