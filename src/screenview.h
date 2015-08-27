#ifndef SCREENVIEW_H
#define SCREENVIEW_H

#include "programmodel.h"

#include <QGraphicsView>
#include "spriteview.h"

/**
 * @brief The ScreenView class
 *
 * @author Brent Chesny
 */
class ScreenView : public QGraphicsView
{
public:
    /**
     * @brief Constructor method
     * @param parent Parent widget
     */
    ScreenView(QWidget *parent = 0);

    /**
     * @brief Destructor method
     */
    ~ScreenView();

    /**
     * @brief Updates the view with the latest information
     */
    void update();

    void setModel(ProgramModel* model) { _model = model; }

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    ProgramModel* _model;

    QGraphicsScene* _scene;

    QList<SpriteView*> _spriteViews;

    // helper methods
    void drawSprites();
    void drawSprite(Sprite* sprite);
    void clearScene();
    SpriteView* getSpriteView(Sprite* sprite);
};

#endif // SCREENVIEW_H
