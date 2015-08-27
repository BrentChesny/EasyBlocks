#include "screenview.h"

#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QDebug>

ScreenView::ScreenView(QWidget *parent) :
    QGraphicsView(parent)
{
    _scene = new QGraphicsScene(0, 0, this->size().height(), this->size().width());
    setScene(_scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

ScreenView::~ScreenView()
{
    delete _scene;
}

void ScreenView::update()
{
    drawSprites();
    if (_model->getScreen()->getBackground() != NULL)
        setBackgroundBrush(QBrush(*(_model->getScreen()->getBackground())));
    else
        setBackgroundBrush(QBrush(_model->getScreen()->getColor()));
}

void ScreenView::drawSprites()
{
    QList<Sprite*> sprites = _model->getSprites();

    for (int i = sprites.size() - 1; i >= 0; --i) {
        drawSprite(sprites.at(i));
    }
}

void ScreenView::drawSprite(Sprite* sprite)
{
    SpriteView* spriteView = getSpriteView(sprite);

    if (spriteView == NULL) {
        spriteView = new SpriteView(sprite);
        _scene->addItem(spriteView);
        _spriteViews.append(spriteView);
    }
    QPixmap pixmap(*(sprite->getCurrentImage()));
    pixmap = pixmap.scaled(sprite->getSize());
    spriteView->setPixmap(pixmap);
    spriteView->setPos(sprite->getPosition().x() - sprite->getSize().width()/2, sprite->getPosition().y() - sprite->getSize().height()/2);
    spriteView->setTransformOriginPoint(sprite->getSize().width()/2, sprite->getSize().height()/2);
    spriteView->setRotation(sprite->getRotation());
    spriteView->setVisible(sprite->getVisible());
}

SpriteView* ScreenView::getSpriteView(Sprite *sprite)
{
    foreach (SpriteView* sv, _spriteViews) {
        if (sv->getSprite() == sprite)
            return sv;
    }

    return NULL;
}

void ScreenView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
        _model->sendSignal(Signal(Signal::ARROW_UP));
    else if (event->key() == Qt::Key_Down)
        _model->sendSignal(Signal(Signal::ARROW_DOWN));
    else if (event->key() == Qt::Key_Left)
        _model->sendSignal(Signal(Signal::ARROW_LEFT));
    else if (event->key() == Qt::Key_Right)
        _model->sendSignal(Signal(Signal::ARROW_RIGHT));
    else if (event->key() == Qt::Key_Return)
        _model->sendSignal(Signal(Signal::ENTER));
    else if (event->key() == Qt::Key_Space)
        _model->sendSignal(Signal(Signal::SPACE));
}
