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

    //Afficher le plateau a chaque tour
    void afficherPlateau();

    //Traitement des click pour le déplacement
    bool traitement(int, int, int, int);

public slots:

    void placerPionBlanc();
    void mousePressEvent(QMouseEvent *actuel);

signals:
    void mousePressed();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene; //Scène pour placer les objets
    QGraphicsPixmapItem *fond; //Image de fond = damier

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

    //Premier click
    int pressXinitial;
    int pressYinitial;

    //Second click
    int pressXsecond;
    int pressYsecond;

    //Instanciation d'un plateau
    Plateau jeu;
};

#endif // MAINWINDOW_H
