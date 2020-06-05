/*	AUTHOR:Sam MAROUN
    DATE: 26/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Window
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Plateau.h"
#include <iostream>

void MainWindow::mousePressEvent(QMouseEvent *actuel)
{
    //On prend la position
    QPointF pt = ui->graphicsView->mapToScene(actuel->pos());

    //qu'on adapte au position pressX et pressY
    pressX = pt.x();
    pressY = pt.y();

    //pressX=5+25*(pressX/25); //position exact du pion en X

    //pressY=5+25*(pressY/25); //position exact du pion en Y

    //On émet le signal pour que le slot soit déclencher
    //emit mousePressed();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //On connecte le SLOT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //On doit le connecter mousseEvent
    //avec la méthode de déplacement de la classe Plateau (POSSIBLE ?)
    QObject::connect(this,SIGNAL(mousePressed()), SLOT(placerPionBlanc()));

    //On initialise la scène
    scene = new QGraphicsScene(this);

    //On définit sa taille en déplaçant la position origine
    scene->setSceneRect(QRectF(0,0,0,0));

    //On lie la scène au graphicView créé
    ui->graphicsView->setScene(scene);

    //On ajoute l'image du damier à cette scène
    fond = scene->addPixmap(QPixmap(":/images/Plateau300-296.jpg"));

    //Initialisation des pions blancs
    whiteBrush = new QBrush();
    whitePen = new QPen();

    //On leur donne leur couleur et leur forme
    whiteBrush->setColor(Qt::white);
    whitePen->setColor(Qt::white);
    whitePen->setWidth(3); //largeur du pinceau
    whiteBrush->setStyle(Qt::SolidPattern);//type de brosse

    //Initialisation des pions blancs
    blackBrush = new QBrush();
    blackPen = new QPen();

    //On leur donne leur couleur et leur forme
    blackBrush->setColor(Qt::black);
    blackPen->setColor(Qt::black);
    blackPen->setWidth(3); //largeur du pinceau
    blackBrush->setStyle(Qt::SolidPattern);//type de brosse



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

/*
std::vector<QGraphicsItem*> MainWindow::getAllItem(){

    //On récupère l'ensemble des items comme variable
    QList<QGraphicsItem *> items = scene->items();
    std::vector<QGraphicsItem*> pions;

    foreach( QGraphicsItem *item, items )

    {

    pions.push_back (item);

    int count = 0;
    for(unsigned int i = 0; i<pions.size();i++)
        count++;
    //Je les stocke dans un tableau et les affiche
    std::cout << count << std::endl;
    }

    pions.erase(pions.begin());
    return pions;
}
*/

void MainWindow::initialisationPlateau(){

    //Placement des Pions Noir
    //Impaire
    for(int i_y=1; i_y<4; i_y+=2){
        for(int i_x=1; i_x<6; i_x++){
            scene->addEllipse(52*i_x,25*i_y,15,15,*blackPen,*blackBrush);
        }
    }

    //Paire
    for(int i_y=0; i_y<3; i_y+=2){
        for(int i_x=0; i_x<5; i_x++){
            scene->addEllipse(52*i_x+25,25*i_y+52,15,15,*blackPen,*blackBrush);
        }
    }

    //Placement des pions Blanc
    //Impaire
    for(int i_y=1; i_y<4; i_y+=2){
        for(int i_x=1; i_x<6; i_x++){
            scene->addEllipse(52*i_x,25*i_y+152,15,15,*whitePen,*whiteBrush);
        }
    }

    //Paire
    for(int i_y=0; i_y<3; i_y+=2){
        for(int i_x=0; i_x<5; i_x++){
            scene->addEllipse(52*i_x+25,25*i_y+204,15,15,*whitePen,*whiteBrush);
        }
    }

}
/*
void MainWindow::afficherPlateau(){
    for(int i_y=0; i_y<10; i_y++){
        for(int i_x=0; i_x<10; i_x++){
            scene->addEllipse();
        }
    }
}
*/

//test qui marche
//void MainWindow::placerPionBlanc(){
  //      scene->addEllipse(pressX,pressY,15,15,*whitePen,*whiteBrush);
//}



//Recupérer les coordonnés d'un pion en cliquant dessus
//puis cliquer sur une case autorisé pour le déplacer
//puis le rendre invisible à sa position de départ et visible à l'arrivé
//tout ça en prenant en compte le fait que d'autres pions sont sur le plateau
