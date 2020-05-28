#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //w.placerPionBlanc();
    w.initialisationPlateau();
    //QMouseEvent *e = nullptr;

    //do{
        //w.mousePressEvent(e);

       // std::cout << w.getPressX() << std::endl;
      //  std::cout << w.getPressY() << std::endl;
    //}while(e != nullptr);


    //delete e;

    return a.exec();
}
