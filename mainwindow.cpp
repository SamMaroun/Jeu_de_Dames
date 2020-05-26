/*	AUTHOR:Sam MAROUN
    DATE: 26/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Window
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //On prend la position
    QPointF pt = ui->graphicsView->mapToScene(e->pos());

    //qu'on adapte au position pressX et pressY
    pressX = pt.x()-30;
    pressY = pt.y()-100;

    //On émet le signal pour que le slot soit déclencher
    emit mousePressed();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //On initialise la scène
    scene = new QGraphicsScene(this);

    //On définit sa taille en déplaçant la position origine
    scene->setSceneRect(QRectF(0,0,0,0));

    //On lie la scène au graphicView créé
    ui->graphicsView->setScene(scene);

    //On ajoute l'image du damier à cette scène
    fond = scene->addPixmap(QPixmap(":/images/Plateau300-296.jpg"));

    //On connecte le SLOT

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getPressX(){
    return pressX;
}

int MainWindow::getPressY(){
    return pressY;
}
