#ifndef SPRITEGRAPHICSITEM_H
#define SPRITEGRAPHICSITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPoint>
#include "spriteresizegraphicsitem.h"

#include "../spriterepr.h"

class EasyBlocksModel;

/**
 * @brief The SpriteGraphicsItem class
 *
 * @author Brecht Vandevoort
 */
class SpriteGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param sprite The SpriteRepr this SpriteGraphicsItem is representing
     * @param parent Parent QGraphicsItem
     */
    SpriteGraphicsItem(SpriteRepr* sprite, EasyBlocksModel* model, QGraphicsItem* parent = 0);

    /**
     * @brief Returns the SpriteRepr this item is observing
     * @return Pointer to a SpriteRepr
     */
    SpriteRepr* getSprite() const {return _sprite;}

    /**
     * @brief Selects the sprite
     */
    void selectSprite();

    /**
     * @brief Deselects the sprite, if selected
     */
    void deselectSprite();

signals:
    void spriteSizeGraphicsUpdated();

public slots:
    /**
     * @brief This function is called when the sprite updates
     */
    void spriteUpdated();

protected:
    /**
     * @brief This function is called when the GraphicsItem changes
     * @param change Parameter of the item that is changing
     * @param value The new value
     * @return The value
     */
    /*QVariant itemChange (GraphicsItemChange change, const QVariant& value);*/

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* contextMenuEvent);

private:
    SpriteRepr* _sprite;
    EasyBlocksModel* _model;
    QPixmap* _pixmap;
    QPoint _clickedPoint;
    bool _ignoreUpdates;
    bool _isSelected;
    SpriteResizeGraphicsItem* _resizer;
};

#endif // SPRITEGRAPHICSITEM_H
