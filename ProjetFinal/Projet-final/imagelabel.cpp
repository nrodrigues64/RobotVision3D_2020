#include "imagelabel.h"

ImageLabel::ImageLabel()
{

}

ImageLabel::ImageLabel(QPixmap q)
{
    this->p = q;
}

void ImageLabel::putPixmap(QPixmap q)
{
    this->p = q;
}

void ImageLabel::resizeEvent(QResizeEvent *event){

    // get label dimensions
    int w = this->width();
    int h = this->height();

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    this->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
}

