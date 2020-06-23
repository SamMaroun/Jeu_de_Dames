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
    if(pressXinitial == -1 && pressYinitial == -1){
       pressXinitial = actuel->y();
       pressYinitial = actuel->x();

       //on affiche là ou peut se déplacer le pion sélectionné
       afficherSurbrillance(pressXinitial,pressYinitial);
    }

    //On prend la position de la case de destination
    else if(pressXinitial != -1 && pressYinitial != -1
            && pressXsecond == -1 && pressYsecond == -1){
        pressXsecond = actuel->y();
        pressYsecond = actuel->x();

        //coorespond à la couleur du pion selectionnée
        int couleur = jeu.getDamier(pressXinitial/25,pressYinitial/25);

        //gestion du tour par tour
        if(auTourDesBlancs){

         //si on est au tour des blancs,
         //il n'y a que les blancs qui peuvent se déplacer
         if(couleur == 1 || couleur == 2){

             //si le traitement renvoie true, le deplacement est possible
             if(traitement(pressXinitial, pressYinitial, pressXsecond, pressYsecond, couleur)){

                 //on realise le signal suivant lié au slot
                 //de mise a jour du plateau
                 emit mousePressed();

                 //au prochain tour ce sera au noir
                 auTourDesBlancs = false;
                 ui->label->setText("<font color=\"#000000\">C'est au tour des Noirs</font>");
             }
         }
        }

        else{

            //si on est au tour des noirs,
            //il n'y a que les blancs qui peuvent se déplacer
            if(couleur == -1 || couleur == -2){

                //si le traitement renvoie true, le deplacement est possible
                if(traitement(pressXinitial, pressYinitial, pressXsecond, pressYsecond, couleur)){

                    //on realise le signal suivant lié au slot
                    //de mise a jour du plateau
                    emit mousePressed();

                    //au prochain tour ce sera au tour des blancs
                    auTourDesBlancs = true;
                    ui->label->setText("<font color=\"#C1C1C1\">C'est au tour des Blancs</font>");

                }
            }
        }

        //on remet les cliques à l'état initial
        pressYinitial=-1;
        pressXinitial=-1;
        pressYsecond=-1;
        pressXsecond=-1;

        //on supprime la surbrillance sur l'ensemble du damier
        supprimerSurbrillance();

        //on teste la condition de victoire à chaque tour
        if(jeu.victoire() != 0){

            if(jeu.victoire() == 1)
                qDebug() << "victoire blanc";

            else if(jeu.victoire() == 2)
                qDebug() << "victoire noir";
        }
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //On nomme notre fenêtre
    setWindowTitle(tr("Jeu de Dame - Sam et Emile"));

    //On initialise la scène
    scene = new QGraphicsScene(this);

    //On définit sa taille en déplaçant la position origine
    scene->setSceneRect(QRectF(0,0,0,0));

    //On lie la scène au graphicView créé
    ui->graphicsView->setScene(scene);

    //On ajoute l'image du damier à cette scène
    fond = scene->addPixmap(QPixmap(":/Plateau250x250.jpg"));

    //Initialisation du bouton de redémarage de partie
    nouvellePartie = new QPushButton("Nouvelle Partie", this);
    nouvellePartie->setGeometry(-1,320,100,25);

    //on connecte le signal released du bouton au slot recommencer
    QObject::connect(nouvellePartie, SIGNAL(released()), this, SLOT(recommencerPartie()));

    //Initialisation du bouton d'instructions
    instructions = new QPushButton("Instructions", this);
    instructions->setGeometry(200,290,100,25);
    checked = false;
    instructions->setChecked(checked);

    QObject::connect(instructions,SIGNAL(toggled(checked)),this,SLOT(afficherRegle(checked)));

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
    yellowBrush = new QBrush(Qt::yellow);
    yellowPen = new QPen(Qt::yellow);

    //On met les cliques souris à -1
    //ce qui ne correspond à aucune case du damier
    pressXinitial = -1;
    pressYinitial = -1;
    pressXsecond = -1;
    pressYsecond = -1;

    //on connecte le slot avec l'affichage du plateau
    QObject::connect(this,SIGNAL(mousePressed()), SLOT(miseAJourPlateau()));

    //gestion du tour par tour
    auTourDesBlancs = true; //les blancs commencent
}

MainWindow::~MainWindow()
{
    delete ui;
}

//A chaque nouveau déplacement on parcourt le damier
//On place alors les pions sur le plateau en fonction de leurs positions
void MainWindow::miseAJourPlateau(){

    //Ici, on supprimer tous les éléments du tableau précédent
    this->supprimerElement();

    //puis on affiche le plateau
    this->afficherPlateau();
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

    //cas du deplacement d'un pion
    if(couleur == -1 || couleur == 1){

        if(jeu.deplacementPion(x_init, y_init, x_dest, y_dest, couleur))
            return true;

        else
            return false;
    }

    //cas du déplcement d'une dame
    else{

        if(jeu.deplacementDame(x_init, y_init, x_dest, y_dest, couleur))
            return true;

        else
            return false;
    }

    return false;
}

void MainWindow::afficherPlateau(){

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

//on affiche la surbrillance permettant d'identifier les déplacements possibles
void MainWindow::afficherSurbrillance(int x, int y){

    x /= 25;
    y /= 25;

    //quand on est au tour des blancs, 2 cas de figure se présentent
    if(auTourDesBlancs){

        //Dans le cas ou nous sommes en dehors du tableau
        //on n'affiche pas la surbrillance
        //on prend aussi en compte qu'on peut faire une prise en arrière
        //comme c'est prévue dans les deplacements

        //cas des pions blancs
        if(jeu.getDamier(x,y) == 1){
            this->surbrillancePion(x,y,1);
        }

        //cas des dames blanches
        else if(jeu.getDamier(x,y) == 2){
            this->surbrillanceDame(x,y,2);
        }
    }

    //de même lorsque c'est au tour des noirs, en adaptant les coordonnées
    else if(!auTourDesBlancs){

        //cas des pions noirs
        if(jeu.getDamier(x,y) == -1){
            this->surbrillancePion(x,y,-1);
        }

        //cas des dames noirs
        else if(jeu.getDamier(x,y) == -2){
            this->surbrillanceDame(x,y,-2);
        }
    }
}

//determination de la surbrillance pour un pion
void MainWindow::surbrillancePion(int x,int y,int couleur){

    //couleur de l'ennemi
    int couleurOpposant = couleur * (-1);

    bool deplacementSimple = true;

    //Soit on peut se deplacer avec prise, et dans ce cas il n'y a
    //pas de deplacement simple

    //deplacement avec prise on gère ensuite tous les deplacements avec prise
    //possible quelque soit la couleur du pion
    //deplacement avec prise vers la gauche en haut
    if( (jeu.getDamier(x-1,y-1) == couleurOpposant
              || jeu.getDamier(x-1,y-1) == couleurOpposant*2)
                && jeu.getDamier(x-2,y-2) == 0
                    && jeu.caseValide(x-2,y-2)){
        scene->addRect(25*(y-2)+7,25*(x-2)+7,14,14,*yellowPen,*yellowBrush);
        deplacementSimple = false;
    }

    //deplacement avec prise vers la gauche en bas
    if( (jeu.getDamier(x+1,y-1) == couleurOpposant
              || jeu.getDamier(x+1,y-1) == couleurOpposant*2)
                && jeu.getDamier(x+2,y-2) == 0
                    && jeu.caseValide(x+2,y-2)){
        scene->addRect(25*(y-2)+7,25*(x+2)+7,14,14,*yellowPen,*yellowBrush);
        deplacementSimple = false;
    }

    //deplacement avec prise vers la gauche bas
    if( (jeu.getDamier(x-1,y+1) == couleurOpposant
             || jeu.getDamier(x-1,y+1) == couleurOpposant*2)
                && jeu.getDamier(x-2,y+2) == 0
                    && jeu.caseValide(x-2,y+2)){
        scene->addRect(25*(y+2)+7,25*(x-2)+7,14,14,*yellowPen,*yellowBrush);
        deplacementSimple = false;
    }

    //deplacement avec prise vers la droite bas
    if( (jeu.getDamier(x+1,y+1) == couleurOpposant
              || jeu.getDamier(x+1,y+1) == couleurOpposant*2)
                && jeu.getDamier(x+2,y+2) == 0
                    && jeu.caseValide(x+2,y+2)){
        scene->addRect(25*(y+2)+7,25*(x+2)+7,14,14,*yellowPen,*yellowBrush);
        deplacementSimple = false;
    }

    if(deplacementSimple){

        //on gère les deplacements simples en fonction de la couleur
        //pion blanc
        if(couleur == 1){

            //deplacement simple vers la gauche
            if(jeu.getDamier(x-1,y-1) == 0 && jeu.caseValide(x-1,y-1)){
                scene->addRect(25*(y-1)+7,25*(x-1)+7,14,14,*yellowPen, *yellowBrush);
            }

            //deplacement simple vers la droite
            if(jeu.getDamier(x-1,y+1) == 0 && jeu.caseValide(x-1,y+1)){
                scene->addRect(25*(y+1)+7,25*(x-1)+7,14,14,*yellowPen,*yellowBrush);
            }
        }

        //pion noir
        else if(couleur == -1){

            //deplacement simple vers la gauche
            if(jeu.getDamier(x+1,y-1) == 0 && jeu.caseValide(x+1,y-1)){
                scene->addRect(25*(y-1)+7,25*(x+1)+7,14,14,*yellowPen,*yellowBrush);
            }

            //deplacement simple vers la droite
            if(jeu.getDamier(x+1,y+1) == 0 && jeu.caseValide(x+1,y+1)){
                scene->addRect(25*(y+1)+7,25*(x+1)+7,14,14,*yellowPen,*yellowBrush);
            }
        }

    }

}

//determination de la surbrillance pour une dame
void MainWindow::surbrillanceDame(int x, int y, int couleur){

    //on ne peut pas se deplacer par dessus ces alliés
    //on crée donc une condition d'arret pour chaque diagonale
    bool stopBasDroite = false ; bool stopBasGauche = false;
    bool stopHautDroite = false; bool stopHautGauche = false;

    //on ne peut pas se deplacer au dessus de deux ennemis ou plus
    //on crée une condition pour verifier le nombre d'ennemi
    //sur la diagonale
    int ennemiBasDroite = 0; int ennemiBasGauche = 0;
    int ennemiHautDroite = 0; int ennemiHautGauche = 0;

    //couleur des ennemies
    int couleurOpposant = couleur * (-1);

    for(int i=1; i<9; i++){

        //deplacement en bas a droite

        //dans chacun des cas, si on rencontre un allié
        //on ne peut pas se deplacer au dela de lui
        if(jeu.getDamier(x+i,y+i) == couleur/2 || jeu.getDamier(x+i,y+i) == couleur){
            stopBasDroite = true;
        }

        //dans chacun des cas si le nombre
        //d'ennemi présent sur la diagonale est au moins à 2
        //ne s'applique pas au delà du deuxieme ennemi
        else if(jeu.getDamier(x+i,y+i) == couleurOpposant/2 || jeu.getDamier(x+i,y+i) == couleurOpposant){
            ennemiBasDroite++;
        }

        //si la case est vide, quelle est valide et quelle respecte
        //les conditions enonces précedemment, on applique la surbrillance
        else if(jeu.getDamier(x+i,y+i) == 0 && jeu.caseValide(x+i,y+i)
                && stopBasDroite == false && ennemiBasDroite < 2){
            scene->addRect(25*(y+i)+7,25*(x+i)+7,14,14,*yellowPen,*yellowBrush);
        }

        //deplacement en bas a gauche
        if(jeu.getDamier(x+i,y-i) == couleur/2 || jeu.getDamier(x+i,y-i) == couleur){
            stopBasGauche = true;
        }

        else if(jeu.getDamier(x+i,y-i) == couleurOpposant/2 || jeu.getDamier(x+i,y-i) == couleurOpposant){
            ennemiBasGauche++;
        }

        else if(jeu.getDamier(x+i,y-i) == 0 && jeu.caseValide(x+i,y-i)
                && stopBasGauche == false && ennemiBasGauche < 2){
            scene->addRect(25*(y-i)+7,25*(x+i)+7,14,14,*yellowPen,*yellowBrush);
        }

         //deplacement en haut a gauche
        if(jeu.getDamier(x-i,y-i) == couleur/2 || jeu.getDamier(x-i,y-i) == couleur){
            stopHautGauche = true;
        }

        else if(jeu.getDamier(x-i,y-i) == couleurOpposant/2 || jeu.getDamier(x-i,y-i) == couleurOpposant){
            ennemiHautGauche++;
        }

        else if(jeu.getDamier(x-i,y-i) == 0 && jeu.caseValide(x-i,y-i)
                && stopHautGauche == false && ennemiHautGauche < 2){
            scene->addRect(25*(y-i)+7,25*(x-i)+7,14,14,*yellowPen,*yellowBrush);
        }

        //deplacement en haut a droite
        if(jeu.getDamier(x-i,y+i) == couleur/2 || jeu.getDamier(x-i,y+i) == couleur){
            stopHautDroite = true;
        }

        else if(jeu.getDamier(x-i,y+i) == couleurOpposant/2 || jeu.getDamier(x-i,y+i) == couleurOpposant){
            ennemiHautDroite++;
        }

        else if(jeu.getDamier(x-i,y+i) == 0 && jeu.caseValide(x-i,y+i)
                && stopHautDroite == false && ennemiHautDroite < 2){
            scene->addRect(25*(y+i)+7,25*(x-i)+7,14,14,*yellowPen,*yellowBrush);
        }
    }
}


//Supprimer l'ensemble des elements du plateau
void MainWindow::supprimerElement(){

    //on supprime l'ensemble des élèments de la scène
    scene->clear();

    //puis on remet le fond
    fond = scene->addPixmap(QPixmap(":/Plateau250x250.jpg"));
}

//Supprimer la surbrillance
void MainWindow::supprimerSurbrillance(){

    //on appelle la methode supprimer element
    this->supprimerElement();

    //On affiche le plateau
    this->afficherPlateau();

}

//remet l'ensemble de la fenetre à son etat initial
//afin de recommencer une nouvelle partie
void MainWindow::recommencerPartie(){

    //on supprime l'ensemble des elements
    this->supprimerElement();

    //et on initialise le plateau console
    Plateau initial;
    jeu = initial;

    //on initialise l'affichage du plateau
    this->afficherPlateau();

    //les blancs qui commencent
    auTourDesBlancs = true;

    //on affiche que c'est à leur tour
    ui->label->setText("<font color=\"#C1C1C1\">C'est au tour des Blancs</font>");

    emit released();//

}

//afficher instruction de jeu
void MainWindow::afficherRegle(bool checked){

    if(checked){
        scene->clear();

    }

    else{
        afficherPlateau();
    }
}
