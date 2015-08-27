#include "blockreprlibrarywidget.h"
#include "userstatementdialog.h"
#include "../userstatementrepr.h"
#include "../blockrepr/userstatementblockrepr.h"
#include "edituserstatementbutton.h"

#include <QDebug>
#include <QStringList>
#include "blockreprview.h"

BlockReprLibraryWidget::BlockReprLibraryWidget(EasyBlocksModel* model, QWidget *parent) :
    QWidget(parent), _model(model)
{
    init();
    setupButtons();
    setupView();
    draw();
}

BlockReprLibraryWidget::~BlockReprLibraryWidget()
{
    if(_addBlockBtnProxy->scene() == NULL)
        delete _addBlockBtnProxy;
}


void BlockReprLibraryWidget::init()
{
    setMinimumWidth(270);
    setMaximumWidth(270);
    _verticalLayout = new QVBoxLayout(this);
    _verticalLayout->setAlignment(Qt::AlignTop);
    setLayout(_verticalLayout);

    _gridLayout = new QGridLayout(this);
    _verticalLayout->addLayout(_gridLayout);

    QPushButton* btn = new QPushButton(tr("Add Block"));
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::transparent);
    btn->setPalette(palette);
    connect(btn, SIGNAL(clicked()), this, SLOT(addBlock()));
    _addBlockBtnProxy = new QGraphicsProxyWidget;
    _addBlockBtnProxy->setWidget(btn);
}

void BlockReprLibraryWidget::setupButtons()
{
    QStringList cats = _model->getProject()->getBlockReprLibrary()->createCategoryList();
    _currentCat = cats.first();
    int i;
    for (i = 0; i < cats.size(); ++i) {
        CategoryButton* btn = new CategoryButton(cats.at(i), tr(cats.at(i).toUtf8().constData()), this);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked(QString)), this, SLOT(buttonClicked(QString)));
        _gridLayout->addWidget(btn, i/2, i%2);
        _buttons.append(btn);
    }

    // user functions button
    CategoryButton* btn = new CategoryButton("User Functions", tr("User Functions"), this);
    btn->setCheckable(true);
    connect(btn, SIGNAL(clicked(QString)), this, SLOT(buttonClicked(QString)));
    _gridLayout->addWidget(btn, i/2, i%2);
    _buttons.append(btn);


    _buttons.first()->setChecked(true);
}

void BlockReprLibraryWidget::setupView()
{
    _view = new QGraphicsView(this);
    _scene = new QGraphicsScene(_view);
    _view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _view->setScene(_scene);
    _verticalLayout->addWidget(_view);
}

void BlockReprLibraryWidget::draw()
{
    QList<BlockRepr*> blocks;
    if (_currentCat != "User Functions")
        blocks.append(_model->getProject()->getBlockReprLibrary()->getBlocksOfCategory(_currentCat));
    else {
        foreach (UserStatementBlockRepr* usbr, _model->getProject()->getUserStatementBlockReprs()) {
            blocks.append(usbr);
        }
    }

    if (_addBlockBtnProxy->scene() != NULL)
        _addBlockBtnProxy->scene()->removeItem(_addBlockBtnProxy);
    _scene->clear();

    QPoint pos(10, 10);
    int i = 0;
    foreach (BlockRepr* br, blocks) {
        if (_currentCat != "User Functions" && !_model->getProject()->getBlockReprLibrary()->isVisible(br))
            continue;
        BlockReprView* brv = BlockReprView::newBlockReprView(br);
        brv->setPos(pos);
        _scene->addItem(brv);

        if (_currentCat == "User Functions") {
            EditUserStatementButton* btn = new EditUserStatementButton(i, tr("Edit"));
            connect(btn, SIGNAL(clicked(int)), this, SLOT(editUserFunc(int)));
            QGraphicsProxyWidget *proxy = _scene->addWidget(btn);
            proxy->setPos(pos + QPoint(br->getTotalSize().width() + 20, 0));
        }

        pos += QPoint(0, br->getTotalSize().height() + 15);
        i++;
    }

    if (_currentCat == "User Functions")
    {
        _scene->addItem(_addBlockBtnProxy);
        _addBlockBtnProxy->setPos(pos);
    }

    _scene->setSceneRect(0, 0, _scene->itemsBoundingRect().toRect().size().width() + 20, _scene->itemsBoundingRect().toRect().size().height() + 20);
}

void BlockReprLibraryWidget::buttonClicked(QString cat)
{
    _currentCat = cat;
    setActiveCategory(cat);
    draw();
}

void BlockReprLibraryWidget::addBlock()
{
    UserStatementDialog dialog;
    if (dialog.exec())
    {
        UserStatementRepr* us = new UserStatementRepr(dialog.getParamDescription(), dialog.getParamTypes(), dialog.getParamNames());
        us->addStartBlock();
        QList<Block::ParamType> types = dialog.getParamTypes();
        QStringList names = dialog.getParamNames();
        for (int i = 0; i < types.size(); ++i) {
            us->addVariable(new VarBlockRepr(types.at(i), names.at(i), _model->getProject(), true));
        }
        _model->getProject()->addUserStatement(us);
        draw();
    }
}

void BlockReprLibraryWidget::editUserFunc(int index)
{
    emit selectedUserFunc(index);
}

void BlockReprLibraryWidget::setActiveCategory(QString cat)
{
    foreach (CategoryButton* btn, _buttons) {
        btn->setChecked(false);
        if (btn->getCategoryName() == cat)
            btn->setChecked(true);
    }
}
