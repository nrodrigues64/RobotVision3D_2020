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
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QSlider>
#include <QComboBox>
#include <QPixmap>
#include <QTimer>
#include <QResizeEvent>
#include <QTcpSocket>
#include <QPushButton>
#include <QDataStream>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QTcpServer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int i = 0,dataSize = 0;
    cv::Mat img1, img2;
    QPushButton *buttonLeft = new QPushButton("&Img Left", this);
    QPushButton *buttonRight = new QPushButton("&Img Right", this);
    QPushButton *buttonDepthMap = new QPushButton("&Dpeth Map", this);
    QGridLayout *layout = new QGridLayout;
    QTcpSocket *socket;
    QTcpServer  _server;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createActions();
private slots:
    void openFileL();
    void openFileR();
    void depthMapEffect();
    void tcpReady();
    void onNewConnection();
};
#endif // MAINWINDOW_H
