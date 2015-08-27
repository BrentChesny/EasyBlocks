#include "blockcanvas.h"

#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

#include "blockmimedata.h"
#include "stringconstantblockreprview.h"

BlockCanvas::BlockCanvas(BlockReprHolder* holder, QObject *parent) :
    QGraphicsScene(parent), _holder(holder)
{
    buildList();
    connect(_holder, SIGNAL(blocksUpdated()), this, SLOT(spriteUpdated()));
    spriteUpdated();
}

BlockCanvas::~BlockCanvas()
{
    resetList();
}

void BlockCanvas::spriteUpdated()
{
    buildList();
}

void BlockCanvas::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsScene::dragMoveEvent(event);
    event->accept();
    event->setDropAction(Qt::MoveAction);
}

void BlockCanvas::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsScene::dragEnterEvent(event);
    event->accept();
}

void BlockCanvas::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsScene::dropEvent(event);

    const BlockMimeData* mime = qobject_cast<const BlockMimeData *>(event->mimeData());
    //check if cast successful
    if (mime) {
        //ignore if drop already successful
        if(mime->getDragInfo()->getDropSuccessful())
            return;

        //get position of drop
        QPoint position = event->scenePos().toPoint() - mime->getDragInfo()->getTopLeft();

        mime->getDragInfo()->getBlockRepr()->setPosition(position);
        mime->getDragInfo()->getBlockRepr()->setHolderParent(_holder);
        _holder->addBlock(mime->getDragInfo()->getBlockRepr());

        mime->getDragInfo()->setDropSuccessful(true);
        mime->getDragInfo()->setKeepOriginal(false);
    }
}

void BlockCanvas::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsScene::dragLeaveEvent(event);
}

void BlockCanvas::resetList()
{
    foreach (BlockReprView* block, _blocks) {
        if(block->scene() != NULL)
            block->scene()->removeItem(block);
        delete block;
    }
    clear();
    //qDeleteAll(_blocks);
    _blocks.clear();
}

void BlockCanvas::buildList()
{
    resetList();

    foreach(BlockRepr* block, _holder->getBlocks()) {
        BlockReprView* blockView = BlockReprView::newBlockReprView(block);
        _blocks.append(blockView);
        blockView->setPos(block->getPosition());
        addItem((QGraphicsItem*)blockView);
    }
}
