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


    //std::vector<QGraphicsItem*> position_pions={};
    //position_pions = w.getAllItem();
    return a.exec();
}
