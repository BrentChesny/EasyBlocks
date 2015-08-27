#ifndef SPRITERESIZEGRAPHICSITEM_H
#define SPRITERESIZEGRAPHICSITEM_H

#include <QGraphicsItem>
#include "rotategraphicsitem.h"
#include "xresizegraphicsitem.h"
#include "yresizegraphicsitem.h"
#include "xyresizegraphicsitem.h"

class SpriteGraphicsItem;

class SpriteResizeGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit SpriteResizeGraphicsItem(SpriteGraphicsItem *parent = 0);

    /**
     * @brief Defines the outer bounds of the item as a rectangle
     * @return The outer bounds of the item
     */
    QRectF boundingRect() const {return _bounds;}

    /**
     * @brief Paints the contents of an item in local coordinates
     * @param painter The QPainter
     * @param option Pointer to QStyleOptionGraphicsItem, provides style options for the item
     * @param widget Pointer to QWidget, points to the widget that is being painted on, optional
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    SpriteGraphicsItem* getParent() const {return _parent;}

signals:

public slots:
    void spriteUpdated();
protected:


private:
    SpriteGraphicsItem* _parent;
    QRect _bounds;
    RotateGraphicsItem* _rotate;
    XResizeGraphicsItem* _xResize;
    YResizeGraphicsItem* _yResize;
    XYResizeGraphicsItem* _xyResize;

};

#endif // SPRITERESIZEGRAPHICSITEM_H
