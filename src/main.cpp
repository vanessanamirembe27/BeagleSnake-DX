#include <QApplication> 
#include "gamewindow.h" add back once implemented pause screen/ title screen 
#include "gameview.h"

int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv); 

    GameWindow window;
    window.showFullScreen();

    return a.exec(); 
}
