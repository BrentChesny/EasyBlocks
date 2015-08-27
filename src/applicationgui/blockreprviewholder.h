#ifndef BLOCKREPRVIEWHOLDER_H
#define BLOCKREPRVIEWHOLDER_H

#include <QGraphicsItem>
#include <QPen>

#include "../block.h"

class BlockRepr;
class BlockReprView;

class BlockReprViewHolder : public QGraphicsItem
{
public:
    /**
     * @brief Constructor
     * @param paramType ReturnType of block that can be placed inside this holder
     * @param index Index of the parameter or body in the block, -1 for nextStatement
     * @param isParam True if the block is a parameter, false if not
     * @param parentBlock The parent BlockReprView containing this instance, NULL not allowed
     */
    BlockReprViewHolder(Block::ParamType paramType, int index, bool isParam, BlockReprView* parentBlock);

    /**
     * @brief Destructor
     */
    ~BlockReprViewHolder();

    /**
     * @brief Defines the outer bounds of the item as a rectangle
     * @return The outer bounds of the item
     */
    QRectF boundingRect() const;

    /**
     * @brief Paints the contents of an item in local coordinates
     * @param painter The QPainter
     * @param option Pointer to QStyleOptionGraphicsItem, provides style options for the item
     * @param widget Pointer to QWidget, points to the widget that is being painted on, optional
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    /**
     * @brief Returns the index of this body or statement in its parent
     * @return The index of this body or statement in its parent
     */
    int getIndex() const {return _index;}

    /**
     * @brief Returns whether or not it's a param
     * @return True if the block is a param, false if not
     */
    bool isParam() const {return _isParam;}

    /**
     * @brief Returns the parent BlockReprView of this block
     * @return The parent BlockReprView of this block
     */
    BlockReprView* getParentBlock() const {return _parentBlock;}

    /**
     * @brief Drops a block in this holder
     * @param block The block to drop
     * @return True if the drop was successful, false if not
     */
    bool dropBlock(BlockRepr *block);

protected:
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);

private:
    Block::ParamType _paramType;
    QBrush _brush;
    QPen _borderPen;

    BlockReprView* _parentBlock;
    int _index;
    bool _isParam;
};

#endif // BLOCKREPRVIEWHOLDER_H
