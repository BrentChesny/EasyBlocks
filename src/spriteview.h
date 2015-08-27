#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include "sprite.h"

#include <QGraphicsPixmapItem>
#include <QMouseEvent>

/**
 * @brief The SpriteView class
 *
 * @author Brent Chesny
 */
class SpriteView : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Constructor method
     * @param sprite The sprite that this view represents
     */
    SpriteView(Sprite* sprite);

    /**
     * @brief Getter for the sprite that this view represents
     * @return The sprite that this view represents
     */
    Sprite* getSprite() const { return _sprite; }
private:
    Sprite* _sprite;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // SPRITEVIEW_H
