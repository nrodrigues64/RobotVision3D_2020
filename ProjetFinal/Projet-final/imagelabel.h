#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
class ImageLabel : public QLabel
{
    QPixmap p;
public:
    ImageLabel();
    ImageLabel(QPixmap);
    void putPixmap(QPixmap);
    void resizeEvent(QResizeEvent*);

};

#endif // IMAGELABEL_H
