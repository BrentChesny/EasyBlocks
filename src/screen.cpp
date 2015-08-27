#include "screen.h"

Screen::Screen()
{
    _size = QSize(700, 500);
    _color = QColor(255, 255, 255);
    _background = NULL;
}

Screen::~Screen()
{
    if(_background != NULL)
        delete _background;
}

void Screen::setColor(QColor color)
{
    if (_background != NULL)
        delete _background;

    _background = NULL;
    _color = color;
}

void Screen::setBackground(QPixmap* pixmap)
{
    if (_background != NULL)
        delete _background;

    _background = pixmap;
}
