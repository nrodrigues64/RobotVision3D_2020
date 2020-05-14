#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <imagelabel.h>
#include <QMainWindow>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QTimer>
#include <QResizeEvent>
#include <QTcpSocket>
#include <QPushButton>
#include <QDataStream>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QTcpServer>
#include "stereoimage.h"

class ServeurTCP : public QMainWindow
{
//Attribut d'un ServeurTCP
    Q_OBJECT
    int i = 0,dataSize = 0;
    cv::Mat imgL,imgR;//Images chargés qui servent à créer notre objet StereoImage
    StereoImage si;//Objet StereoImage qui sert à calculer notre diffMap et le pixel
    QPushButton *buttonLeft = new QPushButton("&Img Left", this);//Bouton
    QPushButton *buttonRight = new QPushButton("&Img Right", this);//Bouton
    QPushButton *buttonDepthMap = new QPushButton("&Get Pixel", this);//Bouton
    QGridLayout *layout = new QGridLayout;
    QTcpSocket *socket; //Socket qui va se connecter à notre serveur
    QTcpServer  _server; //Serveur TCP
//Méthode d'un ServeurTCP
public:
    ServeurTCP(QWidget *parent = nullptr);//Constructeur
    ~ServeurTCP(); //Constructeur
    void createActions(); // Assigne les boutons à leur action
//Fonction qui sont appelée suite à un signal qui a été levé
private slots:
    void openFileL();//Permet d'ouvrir l'image gauche
    void openFileR();//Permet d'ouvrir l'image droite
    void getPixel();//Permet d'envoyer la valeur du pixel calculée
    void tcpReady();//Code qui s'exécute à chaque fois q'un message est reçu depuis le client
    void onNewConnection();//Code qui s'éxécute à chaque nouvelle connection
};
#endif // MAINWINDOW_H
