#include "stereoimage.h"

StereoImage::StereoImage()
{
    imgL = NULL;
    imgR = NULL;
    centerPixel = -10;
}

StereoImage::StereoImage(cv::Mat image1, cv::Mat image2)
{
    imgL = image1.clone();
    imgR = image2.clone();
    centerPixel = depthMapEffect();
}

int StereoImage::getCenterPixel()
{

    return centerPixel;

}

cv::Mat StereoImage::getImgLeft()
{

    return imgL;

}

cv::Mat StereoImage::getImgRight()
{

    return imgR;

}

int StereoImage::depthMapEffect()
{
    int ndisparities = 256;
    int SADWindowSize = 21;


    cv::Mat frame0gray, frame1gray, dispbm, dispnorm_bm;
    cv::cvtColor(imgL, frame0gray, CV_BGR2GRAY);
    cv::cvtColor(imgR, frame1gray, CV_BGR2GRAY);
    cv::Ptr<cv::StereoBM> sbm = cv::StereoBM::create( ndisparities, SADWindowSize);
    double minVal, maxVal;
    sbm->setSpeckleRange(125);
    sbm->setSpeckleWindowSize(150);
    sbm->compute(frame0gray,frame1gray,dispbm);
    cv::minMaxLoc(dispbm, &minVal, &maxVal);
    dispbm.convertTo( dispnorm_bm, CV_8UC1, 255/(maxVal-minVal));
    cv::namedWindow( "Display window", cv::WINDOW_NORMAL );// Create a window for display.
    cv::imshow( "Display window", dispnorm_bm );

    //char* t = (char*)dispnorm_bm.at<uchar>(dispnorm_bm.size().width, dispnorm_bm.size().height);
    qDebug() << "height: " << dispnorm_bm.size().height/2 << ", width: " << dispnorm_bm.size().width/2 << ", pixelV:" << (int)dispnorm_bm.at<uchar>(dispnorm_bm.size().height/2,dispnorm_bm.size().width/2);
    int number= (int)dispnorm_bm.at<uchar>(dispnorm_bm.size().height/2,dispnorm_bm.size().width/2);
    return number;
}
