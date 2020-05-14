#ifndef STEREOIMAGE_H
#define STEREOIMAGE_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

//Classe qui permet d'effectuer des opérations sur des images stéréos
class StereoImage
{

private:
    int centerPixel; //Pixel central
    cv::Mat imgL, imgR; // images stereo
public:
    StereoImage();//Constructeur
    StereoImage(cv::Mat imageL, cv::Mat imageR);//Constructeur
    int getCenterPixel();//Permet de récupérer la valeur de centerPixel
    cv::Mat getImgLeft();//Permet de récupérer imgL
    cv::Mat getImgRight();//Permet de récupérer imgR
    int depthMapEffect();//Calcule la carte de profondeur et récupère la valeur pixel central
};

#endif // STEREOIMAGE_H
