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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //getters et setters
    int getPressX();
    int getPressY();
    std::vector<QGraphicsItem*> getAllItem();

    //Initialisation début de partie
    void initialisationPlateau();

<<<<<<< HEAD
    //Afficher le plateau a chaque tour
    void afficherPlateau();






public slots:
    //void on_actionQuitter_triggerd();


    void placerPionBlanc();

    void mousePressEvent(QMouseEvent *actuel);
    // TEST:void placerPionBlanc();


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

    int pressX;
    int pressY;
};

#endif // MAINWINDOW_H
