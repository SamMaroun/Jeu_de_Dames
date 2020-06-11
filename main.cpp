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

<<<<<<< HEAD

       std::cout << w.getPressX() << std::endl;
       std::cout << w.getPressY() << std::endl;

=======
    //std::vector<QGraphicsItem*> position_pions={};
    //position_pions = w.getAllItem();

>>>>>>> 9802c7669237163bb0ec52000a06ad7f744bacaf
    return a.exec();
}
