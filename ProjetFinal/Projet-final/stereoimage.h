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
    int centerPixel;
    cv::Mat imgL, imgR;
public:
    StereoImage();
    StereoImage(cv::Mat imageL, cv::Mat imageR);
    int getCenterPixel();
    cv::Mat getImgLeft();
    cv::Mat getImgRight();
    int depthMapEffect();
};

#endif // STEREOIMAGE_H
