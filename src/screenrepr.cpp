#include "screenrepr.h"

#include <QBuffer>

ScreenRepr::ScreenRepr(QObject *parent) :
    QObject(parent)
{
    _useImage = false;
    _size = QSize(600, 400);
    _color = QColor(255, 255, 255);
}

void ScreenRepr::setBackgroundColor(QColor color)
{
    _color = color;
    _useImage = false;
    setChanged();
}


void ScreenRepr::setBackgroundImage(QPixmap background)
{
    _image = background;
    _useImage = true;
    setChanged();
}

