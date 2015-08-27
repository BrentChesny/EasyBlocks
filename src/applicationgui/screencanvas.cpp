#include "screencanvas.h"

#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

ScreenCanvas::ScreenCanvas(EasyBlocksModel* model, QObject *parent) :
    QGraphicsScene(parent), _model(model)
{
    connect(_model, SIGNAL(updated()), this, SLOT(projectUpdated()));

    updateSprites();
    updateCanvas();
}

void ScreenCanvas::projectUpdated()
{
    updateSprites();
    updateCanvas();
}


void ScreenCanvas::updateSprites()
{
    //take copy of _sprites
    QList<SpriteGraphicsItem*> sprites = _sprites;

    _sprites.clear();

    //rebuild _sprites
    foreach(SpriteRepr* spriteRepr, _model->getProject()->getSprites()) {
        SpriteGraphicsItem* sgi = getSprite(sprites, spriteRepr);
        if(sgi == NULL) {
            sgi = new SpriteGraphicsItem(spriteRepr, _model);
            addItem(sgi);
        }
        //select sprite if current sprite
        if(_model->getProject()->getCurrentSprite() == spriteRepr)
            sgi->selectSprite();
        else
            sgi->deselectSprite();

        _sprites.append(sgi);
    }

    //remove unused SpriteGraphicsItems
    foreach (SpriteGraphicsItem* sgi, sprites) {
        delete sgi;
    }

    // set z indexes
    QList<SpriteRepr*> spritelist = _model->getProject()->getSprites();
    foreach (SpriteGraphicsItem* s, _sprites) {
        for (int i = 0; i < spritelist.size(); ++i) {
            if (s->getSprite() == spritelist.at(i))
                s->setZValue(spritelist.size() - i);
        }
    }
}

void ScreenCanvas::updateCanvas()
{
    QBrush brush(_model->getProject()->getScreen()->getBackgroundColor());

    if (_model->getProject()->getScreen()->useImage())
        brush = QBrush(_model->getProject()->getScreen()->getBackgroundImage());

    setBackgroundBrush(brush);
}

SpriteGraphicsItem* ScreenCanvas::getSprite(QList<SpriteGraphicsItem*>& sprites, const SpriteRepr* sprite) const
{
    foreach(SpriteGraphicsItem* sgi, sprites)
        if(sgi->getSprite() == sprite) {
            sprites.removeOne(sgi);
            return sgi;
        }

    return NULL;
}

void ScreenCanvas::contextMenuEvent(QGraphicsSceneContextMenuEvent* contextMenuEvent)
{
    QGraphicsScene::contextMenuEvent(contextMenuEvent);

    //ignore if already accepted
    if(contextMenuEvent->isAccepted())
        return;

    QMenu contextMenu(tr("Context menu"));
    contextMenu.addAction(tr("Set background color..."), this, SLOT(setBackgroundColor()));
    contextMenu.addAction(tr("Set background image..."), this, SLOT(setBackgroundImage()));
    contextMenu.exec(contextMenuEvent->screenPos());
}

void ScreenCanvas::setBackgroundColor()
{
    QColor color = QColorDialog::getColor(_model->getProject()->getScreen()->getBackgroundColor(), NULL, tr("Choose a color"));
    if (color.isValid())
        _model->getProject()->getScreen()->setBackgroundColor(color);
}

void ScreenCanvas::setBackgroundImage()
{
    QString path = QFileDialog::getOpenFileName(NULL, tr("Choose an image"), QDir::currentPath(), tr("*.jpg *.png"));

    if (!path.isNull())
    {
        QPixmap* image = new QPixmap(path);
        if (!image->isNull()) {
            _model->getProject()->getScreen()->setBackgroundImage(*image);
            delete image;
        }
    }
}

void ScreenCanvas::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        _model->getProject()->getCurrentSprite()->setPosition(_model->getProject()->getCurrentSprite()->getPosition() + QPoint(-1, 0));
    else if (event->key() == Qt::Key_Right)
        _model->getProject()->getCurrentSprite()->setPosition(_model->getProject()->getCurrentSprite()->getPosition() + QPoint(1, 0));
    else if (event->key() == Qt::Key_Up)
        _model->getProject()->getCurrentSprite()->setPosition(_model->getProject()->getCurrentSprite()->getPosition() + QPoint(0, -1));
    else if (event->key() == Qt::Key_Down)
        _model->getProject()->getCurrentSprite()->setPosition(_model->getProject()->getCurrentSprite()->getPosition() + QPoint(0, 1));
}
