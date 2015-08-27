#ifndef BLOCKCANVAS_H
#define BLOCKCANVAS_H

#include <QGraphicsScene>

#include "../spriterepr.h"
#include "../blockreprholder.h"
#include "blockreprview.h"

/**
 * @brief The BlockCanvas class
 *
 * @author Brecht Vandevoort
 */
class BlockCanvas : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param sprite The SpriteRepr this canvas represents
     * @param parent parent QObject
     */
    explicit BlockCanvas(BlockReprHolder* holder, QObject *parent = 0);

    /**
     * @brief Destructor
     */
    ~BlockCanvas();


public slots:
    /**
     * @brief Slot for listening to updates of the sprite
     */
    void spriteUpdated();

protected:
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);

private:
    BlockReprHolder* _holder;

    QList<BlockReprView*> _blocks;

    /**
     * @brief Resets the list of blocks by deleting each block in the list
     */
    void resetList();

    /**
     * @brief Builds the list of BlockReprView* based on the blocks in _sprite
     */
    void buildList();
};

#endif // BLOCKCANVAS_H
