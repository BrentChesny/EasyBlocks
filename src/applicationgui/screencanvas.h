#ifndef SCREENCANVAS_H
#define SCREENCANVAS_H

#include <QGraphicsScene>

#include "../easyblocksmodel.h"
#include "spritegraphicsitem.h"

/**
 * @brief The ScreenCanvas class
 *
 * @author Brecht Vandevoort
 */
class ScreenCanvas : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param project the opened Project
     * @param parent the parent QObject
     */
    explicit ScreenCanvas(EasyBlocksModel* model, QObject *parent = 0);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* contextMenuEvent);
    void keyPressEvent(QKeyEvent *event);
signals:

public slots:
    /**
     * @brief Slot listens to updates of _project
     */
    void projectUpdated();

    void setBackgroundColor();
    void setBackgroundImage();

private:
    EasyBlocksModel* _model;
    QList<SpriteGraphicsItem*> _sprites;

    /**
     * @brief Updates the list of sprites
     */
    void updateSprites();

    /**
     * @brief Updated the background of the canvas
     */
    void updateCanvas();

    /**
     * @brief Looks for the SpriteGraphicsItem in a list observing the given SpriteRepr, removing the SpriteGraphicsItem from the list
     * @param sprites The list of SpriteGraphicsItem
     * @param sprite The SpriteRepr the SpriteGraphicsItem is observing
     * @return The SpriteGraphicsItem observing sprite, or NULL if not found
     */
    SpriteGraphicsItem* getSprite(QList<SpriteGraphicsItem *> &sprites, const SpriteRepr* sprite) const;
};

#endif // SCREENCANVAS_H
