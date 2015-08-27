#include "spriteblockswidget.h"
#include "blockreprview.h"
#include "../blockrepr/spriteblockrepr.h"

#include <QDebug>

SpriteBlocksWidget::SpriteBlocksWidget(EasyBlocksModel* model, QWidget *parent) :
    QWidget(parent), _model(model)
{
    init();
    connect(_model, SIGNAL(updated()), this, SLOT(update()));
}

SpriteBlocksWidget::~SpriteBlocksWidget()
{
    delete _scene;
    qDeleteAll(_spriteBlockReprs);
}

void SpriteBlocksWidget::init()
{
    setFixedWidth(220);
    _layout = new QVBoxLayout;
    _layout->setAlignment(Qt::AlignTop);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);
    setLayout(_layout);

    _scene = new QGraphicsScene;
    _view = new QGraphicsView(_scene);
    _view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _layout->addWidget(_view);

    draw();
}

void SpriteBlocksWidget::draw()
{
    QList<SpriteRepr*> sprites = _model->getProject()->getSprites();

    _scene->clear();
    qDeleteAll(_spriteBlockReprs);
    _spriteBlockReprs.clear();

    QPoint pos(0, 0);
    foreach (SpriteRepr* sprite, sprites) {
        SpriteBlockRepr* sprblock = new SpriteBlockRepr(sprite, true);
        _spriteBlockReprs.append(sprblock);
        BlockReprView* brv = BlockReprView::newBlockReprView(sprblock);
        brv->setPos(pos);
        _scene->addItem(brv);
        pos += QPoint(0, sprblock->getTotalSize().height() + 15);
    }

    _scene->setSceneRect(-10, -10, _scene->itemsBoundingRect().toRect().size().width(), _scene->itemsBoundingRect().toRect().size().height());
}

void SpriteBlocksWidget::update()
{
    draw();
}
