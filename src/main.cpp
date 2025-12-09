#include <QApplication> 
#include "gamewindow.h"

int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv); 

    GameWindow window; //starts game instance

    window.showFullScreen(); //want full screen on LCD Cape 

    return a.exec(); 
}