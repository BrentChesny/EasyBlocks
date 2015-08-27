#include "variablewidget.h"
#include "variabledialog.h"
#include "blockreprview.h"

#include <QDebug>
#include <QLabel>
#include <QToolButton>

VariableWidget::VariableWidget(EasyBlocksModel* model, QWidget *parent) :
    QWidget(parent), _model(model)
{
    init();
    connect(_model, SIGNAL(updated()), this, SLOT(update()));
}

VariableWidget::~VariableWidget()
{
    delete _scene;
}

void VariableWidget::init()
{
    setFixedWidth(220);
    _layout = new QVBoxLayout;
    _layout->setAlignment(Qt::AlignTop);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);
    setLayout(_layout);

    // create label
    /*QLabel* spritesLabel = new QLabel(tr("Variables"));
    spritesLabel->setAlignment(Qt::AlignLeft);
    QFont font("Arial", 12, QFont::DemiBold);
    font.setPixelSize(12);
    spritesLabel->setFont(font);
    spritesLabel->setContentsMargins(0, 0, 0, 9);
    //_layout->addWidget(spritesLabel);*/

    _scene = new QGraphicsScene;
    _view = new QGraphicsView(_scene);
    _view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _layout->addWidget(_view);

    createButtons();
    draw();
}

void VariableWidget::createButtons()
{
    _btnLayout = new QHBoxLayout;
    _layout->addLayout(_btnLayout);
    QToolButton* addBtn = new QToolButton;
    addBtn->setText("+");
    addBtn->setFixedSize(QSize(20, 20));
    //QToolButton* delBtn = new QToolButton;
    //delBtn->setText("-");
    //delBtn->setFixedSize(QSize(20, 20));
    _btnLayout->addSpacerItem(new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    _btnLayout->addWidget(addBtn);
    //_btnLayout->addWidget(delBtn);

    connect(addBtn, SIGNAL(clicked()), this, SLOT(addVariable()));
    //connect(delBtn, SIGNAL(clicked()), this, SLOT(deleteVariable()));
}

void VariableWidget::addVariable()
{
    VariableDialog dialog;
    if (dialog.exec())
    {
        QString name = dialog.getName();
        if (!_model->getProject()->hasVariableWithName(name))
        {
            //add to sprite if working in sprite
            if(_model->getProject()->getCurrentSprite() != NULL) {
                if (dialog.isGlobal())
                    _model->getProject()->addVariable(new VarBlockRepr(dialog.getType(), name, _model->getProject(), true));
                else
                    _model->getProject()->getCurrentSprite()->addVariable(new VarBlockRepr(dialog.getType(), name, _model->getProject(), true));
            }
            //add to function if working in function
            else if(_model->getProject()->getCurrentFunc() != NULL) {
                _model->getProject()->getCurrentFunc()->addVariable(new VarBlockRepr(dialog.getType(), name, _model->getProject(), true));
            }
        }
    }
}

void VariableWidget::draw()
{
    QList<VarBlockRepr*> vars;
    if (_model->getProject()->getCurrentSpriteIndex() == -1 && _model->getProject()->getCurrentFuncIndex() != -1) {
        vars.append(_model->getProject()->getUserStatements().at(_model->getProject()->getCurrentFuncIndex())->getVars());
    }
    else {
        vars.append(_model->getProject()->getVars());
        if (_model->getProject()->getCurrentSprite() != NULL) {
            QList<VarBlockRepr*> spritevars = _model->getProject()->getCurrentSprite()->getVars();
            vars.append(spritevars);
        }
    }

    _scene->clear();

    QPoint pos(0, 0);
    foreach (VarBlockRepr* var, vars) {
        BlockReprView* brv = BlockReprView::newBlockReprView(var);
        brv->setPos(pos);
        _scene->addItem(brv);
        pos += QPoint(0, var->getTotalSize().height() + 15);
    }

    _scene->setSceneRect(-10, -10, _scene->itemsBoundingRect().toRect().size().width(), _scene->itemsBoundingRect().toRect().size().height());
}

void VariableWidget::update()
{
    draw();
}
