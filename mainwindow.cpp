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
       pressXinitial = actuel->y();
       pressYinitial = actuel->x();

       //afficherSurbrillance(pressXinitial,pressYinitial);
    }

    //On prend la position de la case de destination
    else if(pressXinitial != 0 && pressYinitial != 0
            && pressXsecond == 0 && pressYsecond == 0){
        pressXsecond = actuel->y();
        pressYsecond = actuel->x();

        int couleur = jeu.getDamier(pressXinitial/25,pressYinitial/25);

        //gestion du tour par tour
        if(auTourDesBlancs){
         if(couleur == 1){
             if(traitement(pressXinitial, pressYinitial, pressXsecond, pressYsecond, couleur)){
                 emit mousePressed();
                 auTourDesBlancs = false;
                 qDebug() << auTourDesBlancs;
             }
         }
        }

        else{
            if(couleur == -1){
                if(traitement(pressXinitial, pressYinitial, pressXsecond, pressYsecond, couleur)){
                    emit mousePressed();
                    auTourDesBlancs = true;
                    qDebug() << auTourDesBlancs;
                }
            }
        }

        pressYinitial=0;
        pressXinitial=0;
        pressYsecond=0;
        pressXsecond=0;

        if(jeu.victoire() != 0){

            if(jeu.victoire() == 1)
                qDebug() << "victoire blanc";

            else
                qDebug() << "victoire noir";
        }
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
    fond = scene->addPixmap(QPixmap(":/Plateau250x250.jpg"));

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

    //On met les cliques sourisà 0
    pressXinitial=0;
    pressYinitial=0;
    pressXsecond=0;
    pressYsecond=0;

    //gestion du tour par tour
    auTourDesBlancs = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//On initialise l'ensemble du plateau
void MainWindow::initialisationPlateau(){
    //Placement des Pions Noir
    //Impaire
    for(int x=0; x<10; x++){
        for(int y=0; y<10; y++){

            if(jeu.getDamier(x,y) == 1)
                scene->addEllipse(25*y+7,25*x+7,14,14,*whitePen,*whiteBrush);

            else if(jeu.getDamier(x,y) == -1)
                scene->addEllipse(25*y+7,25*x+7,14,14,*blackPen,*blackBrush);
        }
    }
}

//A chaque nouveau déplacement on parcourt le damier
//On place alors les pions sur le plateau en fonction de leurs positions
void MainWindow::afficherPlateau(){

    //Ici, on supprimer tous les éléments du tableau précédent
    this->supprimerElement();

    //et on place nos pions
    for(int i_x=0; i_x<10; i_x++){
        for(int i_y=0; i_y<10; i_y++){

            //on place les pions blancs
            if(jeu.getDamier(i_x,i_y) == 1){
                scene->addEllipse(25*i_y+7,25*i_x+7,14,14,*whitePen,*whiteBrush);
            }

            //on place les pions noirs
            else if(jeu.getDamier(i_x,i_y) == -1){
                scene->addEllipse(25*i_y+7,25*i_x+7,14,14,*blackPen,*blackBrush);
            }

            //on place les dames blanches
            else if(jeu.getDamier(i_x,i_y) == 2){
                scene->addEllipse(25*i_y+7,25*i_x+7,14,14,*redPen,*whiteBrush);
            }

            //on place les dames noirs
            else if(jeu.getDamier(i_x,i_y) == -2){
                scene->addEllipse(25*i_y+7,25*i_x+7,14,14,*redPen,*blackBrush);
            }
        }
    }
}

//On récupère les cliques de la fonction, on les traite avec la methode
//deplacement de plateau
//true, si le traitement à réussi
bool MainWindow::traitement(int x_init, int y_init, int x_dest, int y_dest, int couleur){

    //La taille d'une case est de 25px
    //on identifie avec cela les cases considérées
    x_init /= 25;
    y_init /= 25;

    x_dest /= 25;
    y_dest /= 25;

    //si le deplacement est possible
    if(jeu.deplacementPion(x_init, y_init, x_dest, y_dest, couleur))
        return true;

    else
        return false;

    return false;
}

/*
void MainWindow::afficherSurbrillance(int x, int y){
    x /= 25;
    y /= 25;
}
*/

//Supprimer l'ensemble des elements du plateau
void MainWindow::supprimerElement(){
    scene->clear();
    fond = scene->addPixmap(QPixmap(":/Plateau250x250.jpg"));
}

//Recupérer les coordonnés d'un pion en cliquant dessus
//puis cliquer sur une case autorisé pour le déplacer
//puis le rendre invisible à sa position de départ et visible à l'arrivé
//tout ça en prenant en compte le fait que d'autres pions sont sur le plateau
