#ifndef SPRITEBLOCKSWIDGET_H
#define SPRITEBLOCKSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "../easyblocksmodel.h"

class SpriteBlockRepr;

class SpriteBlocksWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteBlocksWidget(EasyBlocksModel* model, QWidget *parent = 0);

    ~SpriteBlocksWidget();

public slots:
    void update();

private:
    EasyBlocksModel* _model;
    QVBoxLayout* _layout;
    QGraphicsView* _view;
    QGraphicsScene* _scene;
    QList<SpriteBlockRepr*> _spriteBlockReprs;

    void init();
    void draw();
};

#endif // SPRITEBLOCKSWIDGET_H
