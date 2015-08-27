#include "spritegraphicsitem.h"
#include "../easyblocksmodel.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMatrix>

SpriteGraphicsItem::SpriteGraphicsItem(SpriteRepr *sprite, EasyBlocksModel* model, QGraphicsItem *parent)
    : QObject(NULL), QGraphicsPixmapItem(parent), _sprite(sprite), _model(model), _ignoreUpdates(false), _isSelected(false), _resizer(NULL)
{
    spriteUpdated();
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsMovable);
    //setFlag(QGraphicsItem::ItemIsSelectable);

    connect(_sprite, SIGNAL(graphicsUpdated()), this, SLOT(spriteUpdated()));
}

void SpriteGraphicsItem::selectSprite()
{
    //ignore if already selected
    if(_isSelected)
        return;
    _isSelected  = true;

    //draw resizer
    _resizer = new SpriteResizeGraphicsItem(this);
}

void SpriteGraphicsItem::deselectSprite()
{
    //ignore if not selected
    if(!_isSelected)
        return;
    _isSelected = false;

    //delete resizer
    delete _resizer;
    _resizer = NULL;
}

void SpriteGraphicsItem::spriteUpdated()
{
    if(_ignoreUpdates)
        return;

    setPixmap(_sprite->getCurrentImage().scaled(_sprite->getSize(), Qt::IgnoreAspectRatio));
    //setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
    setOffset(-boundingRect().width()/2, -boundingRect().height()/2);
    setPos(_sprite->getPosition());
    setRotation(_sprite->getRotation());

    emit spriteSizeGraphicsUpdated();
}

/*QVariant SpriteGraphicsItem::itemChange (GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedChange)
        qDebug() << (QObject*)this << "changed selection";

    return QGraphicsItem::itemChange(change, value);
}*/

void SpriteGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //ignore updates while dragging
    _ignoreUpdates = true;
    //call base class implementation
    QGraphicsPixmapItem::mousePressEvent(event);

    //set the clicked point
    _clickedPoint = event->pos().toPoint();
    //rotate coords to match scene axis
    QMatrix m;
    //m.translate(boundingRect().width()/2, boundingRect().height()/2);
    m.rotate(_sprite->getRotation());
    //m.translate(-boundingRect().width()/2, -boundingRect().height()/2);
    _clickedPoint = m.map(_clickedPoint);
}

void SpriteGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);

    //set new position
    _sprite->setPosition(event->scenePos().toPoint() - _clickedPoint);
    _model->getProject()->setCurrentSprite(_sprite);
    setPos(event->scenePos() - _clickedPoint);
}

void SpriteGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    _sprite->setPosition(event->scenePos().toPoint() - _clickedPoint);
    _model->getProject()->setCurrentSprite(_sprite);
    _ignoreUpdates = false;
}


void SpriteGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* contextMenuEvent)
{
    contextMenuEvent->accept();
}
