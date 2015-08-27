#ifndef BLOCKREPRVIEW_H
#define BLOCKREPRVIEW_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QDrag>
#include <QGraphicsSceneContextMenuEvent>

#include "../blockrepr.h"
#include "blockreprviewholder.h"

/**
 * @brief The BlockReprView class
 *
 * @author Brecht Vandevoort
 */
class BlockReprView : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:

    /**
     * @brief Creates a new BlockReprView or subclass of it based on given BlockRepr
     * @param blockRepr The BlockRepr to create a view for
     * @param parent The parent item
     * @return Pointer to the created BlockReprView
     */
    static BlockReprView* newBlockReprView(BlockRepr* blockRepr, QGraphicsItem *parent = 0);

    /**
     * @brief Destructor
     */
    virtual ~BlockReprView();

    /**
     * @brief Defines the outer bounds of the item as a rectangle
     * @return The outer bounds of the item
     */
    virtual QRectF boundingRect() const {return _bounds;}

    /**
     * @brief Returns the shape of the block
     * @return The shape of the block
     */
    virtual QPainterPath shape () const {return _shape;}

    /**
     * @brief Paints the contents of an item in local coordinates
     * @param painter The QPainter
     * @param option Pointer to QStyleOptionGraphicsItem, provides style options for the item
     * @param widget Pointer to QWidget, points to the widget that is being painted on, optional
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    BlockRepr* getBlockRepr() const {return _blockRepr;}

public slots:
    /**
     * @brief Updates the boundingRect and the position of the child blocks
     */
    virtual void updateBlock();

protected:

    /**
     * @brief Constructor
     * @param parent Pointer to the parent item
     */
    explicit BlockReprView(BlockRepr* blockRepr, QGraphicsItem *parent = 0);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

private:
    BlockRepr* _blockRepr;
    QGraphicsItem** _params;
    bool* _isParamHolder;
    QGraphicsItem** _bodies;
    bool* _isBodyHolder;
    QGraphicsItem* _nextStatement;
    bool _isNextStatementHolder;
    QPolygon _polygon;
    QRectF _bounds;
    QPainterPath _shape;

    /**
     * @brief Creates an array containing the points to draw the polygon
     * @return An array containing the corner points of the polygon
     */
    QPoint* createPolygonPoints() const;

    QPolygon createPolygon() const;

    /**
     * @brief Initializes the BlockReprView, based on the BlockRepr
     */
    void init();

    /**
     * @brief Resets the holders of the different params and bodies
     */
    void resetHolders();

    /**
     * @brief Sets the pixmap of the cursor in the drag to this block
     * @param drag The QDrag object
     */
    void setCursorPixmap(QDrag* drag, QPoint position);
};

#endif // BLOCKREPRVIEW_H
