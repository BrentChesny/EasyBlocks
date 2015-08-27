#include "blockreprviewholder.h"

#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

#include "blockcolors.h"
#include "../blockrepr.h"
#include "blockreprview.h"
#include "blockmimedata.h"

BlockReprViewHolder::BlockReprViewHolder(Block::ParamType paramType, int index, bool isParam, BlockReprView *parentBlock) :
    QGraphicsItem(parentBlock), _paramType(paramType), _parentBlock(parentBlock), _index(index), _isParam(isParam)
{
    _brush.setColor(BlockColors::getColor(_paramType).lighter(125));
    _brush.setStyle(Qt::SolidPattern);
    _borderPen = QPen(Qt::black);
    setAcceptDrops(true);
}

BlockReprViewHolder::~BlockReprViewHolder()
{

}

QRectF BlockReprViewHolder::boundingRect() const
{
    return QRectF(QPointF(0, 0), BlockRepr::HOLDER_SIZE);
}

void BlockReprViewHolder::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*painter->setBrush(QBrush(QColor(255, 255, 255)));*/
    painter->setPen(_borderPen);
    /*painter->drawRect(boundingRect());*/
    painter->setBrush(_brush);
    painter->drawRect(boundingRect());
}

bool BlockReprViewHolder::dropBlock(BlockRepr* block)
{
    return ((_isParam && _parentBlock->getBlockRepr()->placeParam(block, _index)))
                    || (!_isParam && _index >=0 && _parentBlock->getBlockRepr()->placeBody(block, _index))
                    || (!_isParam && _index < 0 && _parentBlock->getBlockRepr()->placeNextStatement(block));
}

void BlockReprViewHolder::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsItem::dragEnterEvent(event);

    const BlockMimeData* mime = qobject_cast<const BlockMimeData *>(event->mimeData());
    //check if cast successful
    if (mime) {

        //ignore if this block is locked
        if(_parentBlock->getBlockRepr()->isLocked())
            return;

        if((_isParam && _parentBlock->getBlockRepr()->doesParamFit(mime->getDragInfo()->getBlockRepr(), _index))
                || (!_isParam && _parentBlock->getBlockRepr()->doesBodyFit(mime->getDragInfo()->getBlockRepr(), _index)))
        {
            _brush.setStyle(Qt::SolidPattern);
            _borderPen = QPen(Qt::white);
            update(boundingRect());
        }
    }
}

void BlockReprViewHolder::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsItem::dropEvent(event);

    const BlockMimeData* mime = qobject_cast<const BlockMimeData *>(event->mimeData());
    //check if cast successful
    if (mime) {
        //ignore if drop already successful
        if(mime->getDragInfo()->getDropSuccessful())
            return;

        //ignore if this block is locked
        if(_parentBlock->getBlockRepr()->isLocked())
            return;

        //if drop successful
        if(dropBlock(mime->getDragInfo()->getBlockRepr()))
        {
            mime->getDragInfo()->setDropSuccessful(true);
            mime->getDragInfo()->setKeepOriginal(false);
        }
    }
}

void BlockReprViewHolder::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsItem::dragLeaveEvent(event);

    _brush.setStyle(Qt::SolidPattern);
    _borderPen = QPen(Qt::black);
    update(boundingRect());
}
