/*	AUTHOR:Sam MAROUN
    DATE: 26/05/2020
    NAME:Plateau.cpp
    DESCRIPTION:Déclaration de la classe Window
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>
#include <QTextEdit>
#include <QLabel>

#include "Plateau.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Initialisation début de partie
    void initialisationPlateau();

    //Traitement des cliques pour le déplacement
    bool traitement(int, int, int, int, int);

    //Afficher la surbrillance
    //void afficherSurbrillance(int, int);

    //Supprimer l'ensemble des elements du plateau
    void supprimerElement();

public slots:
    void mousePressEvent(QMouseEvent *actuel);

    //Afficher le plateau a chaque tour
    void afficherPlateau();

signals:
    void mousePressed();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene; //Scène pour placer les objets
    QGraphicsPixmapItem *fond; //Image de fond = damier
    QLabel *label; //Permet d'afficher a Qui est le tours

    //Dessiner les pions Blancs
    QGraphicsEllipseItem *pionBlanc; //pion
    QBrush *whiteBrush; //Brosse Blanche
    QPen *whitePen; //Crayon Blanc

    //Dessiner les pions Noirs
    QGraphicsEllipseItem *pionNoir;
    QBrush *blackBrush;
    QPen *blackPen;

    //Dessiner les dames
    QPen *redPen;

    //Dessiner surbrillance
    QGraphicsRectItem *surbrillance;
    QBrush *yellowBrush;
    QPen *yellowPen;

    //gestion clique de souris
    int pressXinitial;
    int pressYinitial;
    int pressXsecond;
    int pressYsecond;

    //gestion du tour par tour
    bool auTourDesBlancs;

    //Instanciation d'un plateau
    Plateau jeu;
};

#endif // MAINWINDOW_H
