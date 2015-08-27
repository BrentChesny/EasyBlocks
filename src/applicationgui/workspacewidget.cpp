#include "workspacewidget.h"

#include <QDebug>

#include "../mainwindow.h"
#include "spriteswidget.h"
#include "spriteblockswidget.h"
#include "sizedialog.h"

WorkspaceWidget::WorkspaceWidget(EasyBlocksModel* model, MainWindow *window, QWidget *parent) :
    QWidget(parent), _model(model), _window(window), _blockCanvas(NULL), _blockScale(1.0)
{
    init();
    connect(_model, SIGNAL(updated()), this, SLOT(update()));
    connect(_model, SIGNAL(projectLoaded()), this, SLOT(renewBlockCanvas()));
}

void WorkspaceWidget::setBlockReprLibWidget(BlockReprLibraryWidget *widget)
{
    _brlw = widget;
    connect(_brlw, SIGNAL(selectedUserFunc(int)), this, SLOT(userFuncSelected(int)));
}


void WorkspaceWidget::init()
{
    _horizontalLayout = new QHBoxLayout;
    _horizontalLayout->setContentsMargins(0, 12, 12, 12);
    setLayout(_horizontalLayout);

    _tabs = new QTabWidget;
    _blockCanvasView = new QGraphicsView;
    _blockCanvasView->setAcceptDrops(true);
    _blockCanvas = new BlockCanvas(_model->getProject()->getCurrentSprite());
    _blockCanvasView->setScene(_blockCanvas);
    _blockCanvas->setSceneRect(0, 0, 10000, 10000);
    _blockCanvasView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _blockCanvasView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //_blockCanvasView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _tabs->addTab(_blockCanvasView, tr("Block Canvas"));
    spriteSelectionChanged(0);

    _screenCanvasView = new QGraphicsView;
    _screenCanvas = new ScreenCanvas(_model, this);
    _screenCanvasView->setScene(_screenCanvas);
    _screenCanvasView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _screenCanvasView->setMaximumSize(_model->getProject()->getScreen()->getSize().width() + 2, _model->getProject()->getScreen()->getSize().height() + 2);
    _screenCanvasView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    _screenCanvas->setSceneRect(0, 0, _model->getProject()->getScreen()->getSize().width(), _model->getProject()->getScreen()->getSize().height());
    _tabs->addTab(_screenCanvasView, tr("Screen Canvas"));

    _spriteProperties = new SpritePropertiesWidget(_model);

    _extraBlocks = new QTabWidget;
    _extraBlocks->setStyleSheet("QTabWidget::pane { border:none; }");
    _extraBlocks->addTab(new VariableWidget(_model), tr("Variables"));
    _extraBlocks->addTab(new SpriteBlocksWidget(_model), tr("Spriteblocks"));

    QMenu* _backgroundMenu = new QMenu(this);
    _backgroundMenu->addAction(tr("Set background color..."), _screenCanvas, SLOT(setBackgroundColor()));
    _backgroundMenu->addAction(tr("Set background image..."), _screenCanvas, SLOT(setBackgroundImage()));
    _backgroundMenu->addAction(tr("Set screen size..."), this, SLOT(setScreenSize()));
    _backgroundOptions = new QToolButton;
    _backgroundOptions->setText(tr("Screen Options"));
    _backgroundOptions->setFixedHeight(20);
    _backgroundOptions->setMenu(_backgroundMenu);
    _backgroundOptions->setPopupMode(QToolButton::InstantPopup);
    _backgroundOptions->setArrowType(Qt::NoArrow);
    _backgroundOptions->setStyleSheet(QString("QToolButton::menu-indicator { image: none; }"));

    QWidget* subwidget = new QWidget;
    subwidget->setLayout(new QGridLayout);
    subwidget->layout()->setContentsMargins(0, 0, 0, 0);
    subwidget->layout()->addWidget(_spriteProperties);
    subwidget->layout()->addWidget(_backgroundOptions);

    _stackedWidget = new QStackedWidget;
    _stackedWidget->setFixedWidth(220);
    _stackedWidget->addWidget(_extraBlocks);
    _stackedWidget->addWidget(subwidget);

    _verticalLayout = new QVBoxLayout;
    _verticalLayout->addWidget(new SpritesWidget(_model, this));
    _verticalLayout->addWidget(_stackedWidget);

    _horizontalLayout->addWidget(_tabs);
    _horizontalLayout->addLayout(_verticalLayout);

    connect(_tabs, SIGNAL(currentChanged(int)), _stackedWidget, SLOT(setCurrentIndex(int)));
    connect(_tabs, SIGNAL(currentChanged(int)), _window, SLOT(disableToolsBasedOnTab(int)));
}

void WorkspaceWidget::spriteSelectionChanged(int index)
{
    if (index < 0) {
        _blockCanvasView->setScene(NULL);
        return;
    }

    _model->getProject()->setCurrentSpriteIndex(index);
    if (_blockCanvas != NULL)
        delete _blockCanvas;

    _blockCanvas = new BlockCanvas(_model->getProject()->getCurrentSprite(), this);
    _blockCanvasView->setScene(_blockCanvas);
    _blockCanvas->setSceneRect(0, 0, 10000, 10000);
    _blockCanvasView->ensureVisible(0, 0, 1, 1);
    _blockCanvasView->scroll(-10000,-10000);
}

void WorkspaceWidget::setScreenSize()
{
    QSize size = _model->getProject()->getScreen()->getSize();

    SizeDialog dialog(&size);
    dialog.exec();

    _model->getProject()->getScreen()->setSize(size);
}

void WorkspaceWidget::update()
{
    _screenCanvasView->setMaximumSize(_model->getProject()->getScreen()->getSize().width() + 2, _model->getProject()->getScreen()->getSize().height() + 2);
    _screenCanvas->setSceneRect(0, 0, _model->getProject()->getScreen()->getSize().width(), _model->getProject()->getScreen()->getSize().height());
}

void WorkspaceWidget::renewBlockCanvas()
{
    _blockCanvas = new BlockCanvas(_model->getProject()->getCurrentSprite(), this);
    _blockCanvasView->setScene(_blockCanvas);
    _blockCanvas->setSceneRect(0, 0, 10000, 10000);
    _blockCanvasView->ensureVisible(0,0,1,1);
    _blockCanvasView->scroll(-10000,-10000);
}

void WorkspaceWidget::userFuncSelected(int index)
{
    _model->getProject()->setCurrentFuncIndex(index);
    _blockCanvas = new BlockCanvas(_model->getProject()->getUserStatements().at(index), this);
    _blockCanvasView->setScene(_blockCanvas);
    _blockCanvas->setSceneRect(0, 0, 10000, 10000);
    _blockCanvasView->ensureVisible(0, 0, 1, 1);
    _blockCanvasView->scroll(-10000,-10000);
}

void WorkspaceWidget::incrementBlockViewScale()
{
    _blockCanvasView->scale(1.0/_blockScale, 1.0/_blockScale);
    _blockScale += 0.1;
    if (_blockScale > 3.0)
        _blockScale = 3.0;
    _blockCanvasView->scale(_blockScale, _blockScale);
}

void WorkspaceWidget::decrementBlockViewScale()
{
    _blockCanvasView->scale(1.0/_blockScale, 1.0/_blockScale);
    _blockScale -= 0.1;
    if (_blockScale < 0.2)
        _blockScale = 0.2;
    _blockCanvasView->scale(_blockScale, _blockScale);
}
