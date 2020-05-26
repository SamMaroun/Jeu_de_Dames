#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRectF(0,0,700,700));
    ui->graphicsView->setScene(scene);
    fond = scene->addPixmap(QPixmap(":/Plateau600-591.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
