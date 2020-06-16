/*	AUTHOR:Sam MAROUN
    DATE: 26/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Window
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

void MainWindow::mousePressEvent(QMouseEvent *actuel)
{
    //On prend la position du premier clique
    if(pressXinitial == 0 && pressYinitial == 0){
       pressXinitial = actuel->globalX();
       pressYinitial = actuel->globalY();

       //afficherSurbrillance(pressXinitial,pressYinitial);
    }

    //On prend la position de la case de destination
    else if(pressXinitial != 0 && pressYinitial != 0){
        pressXsecond = actuel->globalX();
        pressYsecond = actuel->globalY();

    }

    if(traitement(pressXinitial, pressYinitial, pressXsecond, pressYsecond)){
        emit mousePressed();

        pressXinitial=0;
        pressYinitial=0;
    }
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

    //Initialisation des pions blancs
    whiteBrush = new QBrush();
    whitePen = new QPen();

    //On leur donne leur couleur et leur forme
    whiteBrush->setColor(Qt::white);
    whitePen->setColor(Qt::white);
    whitePen->setWidth(3); //largeur du pinceau
    whiteBrush->setStyle(Qt::SolidPattern);//type de brosse

    //Initialisation des pions noir
    blackBrush = new QBrush();
    blackPen = new QPen();

    //On leur donne leur couleur et leur forme
    blackBrush->setColor(Qt::black);
    blackPen->setColor(Qt::black);
    blackPen->setWidth(3); //largeur du pinceau
    blackBrush->setStyle(Qt::SolidPattern);//type de brosse

    //Initialisation dames
    redPen = new QPen();
    redPen->setColor(Qt::red);
    redPen->setWidth(3); //largeur du pinceau

    //Surbrillance
    yellowBrush = new QBrush;
    yellowPen = new QPen;

    yellowBrush->setColor(Qt::yellow);
    yellowPen->setColor(Qt::yellow);
    yellowPen->setWidth(3);
    yellowBrush->setStyle(Qt::SolidPattern);

    //on connecte le slot avec l'affichage du plateau
    QObject::connect(this,SIGNAL(mousePressed()), SLOT(afficherPlateau()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//On initialise l'ensemble du plateau
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

//A chaque nouveau déplacement on parcourt le damier
//On place alors les pions sur le plateau en fonction de leurs positions
void MainWindow::afficherPlateau(){
    for(int i_y=0; i_y<10; i_y++){
        for(int i_x=0; i_x<10; i_x++){

            //on place les pions blancs
            if(jeu.getDamier(i_x,i_y) == 1){
                scene->addEllipse(25*i_x,25*i_y,15,15,*whitePen,*whiteBrush);
            }

            //on place les pions noirs
            else if(jeu.getDamier(i_x,i_y) == -1){
                scene->addEllipse(25*i_x,25*i_y,15,15,*blackPen,*blackBrush);
            }

            //on place les dames blanches
            if(jeu.getDamier(i_x,i_y) == 2){
                scene->addEllipse(25*i_x,25*i_y,15,15,*redPen,*whiteBrush);
            }

            //on place les dames noirs
            else if(jeu.getDamier(i_x,i_y) == -2){
                scene->addEllipse(25*i_x,25*i_y,15,15,*redPen,*blackBrush);
            }
        }
    }
}

/*
void MainWindow::afficherSurbrillance(int x, int y){
    x /= 25;
    y /= 25;



}
*/

//On récupère les cliques de la fonction, on les traite avec la methode
//deplacement de plateau
//true, si le traitement à réussi
bool MainWindow::traitement(int x_init, int y_init, int x_dest, int y_dest){

    //La taille d'une case est de 25px
    //on identifie avec cela les cases considérées
    x_init /= 25;
    y_init /= 25;

    x_dest /= 25;
    y_dest /= 25;

    //SAMAMAMAMAMA::::::Modifier 0 et 1 car pas clair
    if(jeu.deplacementPion(x_init, y_init, x_dest, y_dest) == 0)
        return true;

    else if(jeu.deplacementPion(x_init, y_init, x_dest, y_dest) == 1)
        return false;

   return false;
}




//Recupérer les coordonnés d'un pion en cliquant dessus
//puis cliquer sur une case autorisé pour le déplacer
//puis le rendre invisible à sa position de départ et visible à l'arrivé
//tout ça en prenant en compte le fait que d'autres pions sont sur le plateau
