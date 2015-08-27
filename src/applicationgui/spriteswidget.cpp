#include "spriteswidget.h"
#include "spriteimagedialog.h"

#include <QLabel>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <QFileDialog>

SpritesWidget::SpritesWidget(EasyBlocksModel* model, WorkspaceWidget* wsw, QWidget *parent) :
    QWidget(parent), _workspace(wsw), _model(model)
{
    init();
    connect(_model, SIGNAL(updated()), this, SLOT(update()));
    connect(_model, SIGNAL(projectLoaded()), this, SLOT(drawSprites()));
}

void SpritesWidget::init()
{
    setFixedWidth(220);
    _layout = new QVBoxLayout;
    _layout->setAlignment(Qt::AlignTop);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);
    setLayout(_layout);

    // create label
    QLabel* spritesLabel = new QLabel(tr("Sprites"));
    spritesLabel->setAlignment(Qt::AlignLeft);
    QFont font("Arial", 12, QFont::DemiBold);
    font.setPixelSize(12);
    spritesLabel->setFont(font);
    spritesLabel->setContentsMargins(0, 0, 0, 9);
    _layout->addWidget(spritesLabel);
    createSpritesList();

    createButtons();
}

void SpritesWidget::createSpritesList()
{
    _listWidget = new QListWidget;
    _listWidget->setFocusPolicy(Qt::NoFocus);
    _listWidget->setIconSize(QSize(48, 48));
    _listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    _listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(_listWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
    connect(_listWidget, SIGNAL(currentRowChanged(int)), _workspace, SLOT(spriteSelectionChanged(int)));
    connect(_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectSprite(QListWidgetItem*)));
    _layout->addWidget(_listWidget);

    drawSprites();
}

void SpritesWidget::createButtons()
{
    _btnLayout = new QHBoxLayout;
    _layout->addLayout(_btnLayout);
    QToolButton* upBtn = new QToolButton;
    upBtn->setText("^");
    upBtn->setFixedSize(QSize(20, 20));
    QToolButton* downBtn = new QToolButton;
    downBtn->setText("v");
    downBtn->setFixedSize(QSize(20, 20));
    QToolButton* addBtn = new QToolButton;
    addBtn->setText("+");
    addBtn->setFixedSize(QSize(20, 20));
    QToolButton* delBtn = new QToolButton;
    delBtn->setText("-");
    delBtn->setFixedSize(QSize(20, 20));
    _btnLayout->addSpacerItem(new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    _btnLayout->addWidget(upBtn);
    _btnLayout->addWidget(downBtn);
    _btnLayout->addWidget(addBtn);
    _btnLayout->addWidget(delBtn);

    QMenu* menu = new QMenu(this);
    menu->addAction(tr("Add sprite from file"), this, SLOT(addSpriteFromFileAction()));
    addBtn->setMenu(menu);
    addBtn->setPopupMode(QToolButton::InstantPopup);
    addBtn->setArrowType(Qt::NoArrow);
    addBtn->setStyleSheet(QString("QToolButton::menu-indicator { image: none; }"));

    connect(delBtn, SIGNAL(clicked()), this, SLOT(deleteSpriteAction()));
    connect(upBtn, SIGNAL(clicked()), this, SLOT(moveUpAction()));
    connect(downBtn, SIGNAL(clicked()), this, SLOT(moveDownAction()));
}

int SpritesWidget::getSelectedIndex()
{
    int selected;
    QList<QListWidgetItem*> items = _listWidget->selectedItems();

    if (items.isEmpty())
        return -1;

    selected = _listWidget->row(items.first());
    return selected;
}

void SpritesWidget::drawSprites()
{
    _listWidget->clear();
    QList<SpriteRepr*> sprites = _model->getProject()->getSprites();
    foreach (SpriteRepr* sprite, sprites) {
        QIcon icon(*(sprite->getImages().first()));
        QListWidgetItem* item = new QListWidgetItem(icon, sprite->getName());
        item->setSizeHint(QSize(58, 58));
        _listWidget->addItem(item);
    }
    if (_model->getProject()->getCurrentSpriteIndex() >= 0)
        _listWidget->setCurrentRow(_model->getProject()->getCurrentSpriteIndex());
}

void SpritesWidget::selectSprite(QListWidgetItem *qListWidgetItem)
{
    _workspace->spriteSelectionChanged(getSelectedIndex());
}

void SpritesWidget::showContextMenu(const QPoint &pos)
{
    QListWidgetItem* item = _listWidget->itemAt(pos);
    if(item == NULL)
        return;

    _listWidget->setCurrentItem(item);
    QMenu contextMenu(tr("Context menu"), this);
    contextMenu.addAction(tr("Edit Images..."), this, SLOT(editImagesAction()));
    contextMenu.addAction(tr("Duplicate"), this, SLOT(duplicateSpriteAction()));
    contextMenu.addAction(tr("Delete") + " '" + item->text() + "'", this, SLOT(deleteSpriteAction()));
    contextMenu.exec(mapToGlobal(pos));

}

void SpritesWidget::addSpriteFromFileAction()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Files"), QDir::currentPath(), tr("*.jpg *.png"));

    if (!path.isNull())
    {
        QPixmap* image = new QPixmap(path);
        if (!image->isNull())
        {
            QFileInfo info(path);
            _model->getProject()->addSprite(image, info.baseName());
            drawSprites();
        }
    }
}

void SpritesWidget::deleteSpriteAction()
{
    int selected = getSelectedIndex();
    _model->getProject()->removeSprite(selected);
    drawSprites();
}

void SpritesWidget::duplicateSpriteAction()
{
    _model->getProject()->duplicateCurrentSprite();
    drawSprites();
}

void SpritesWidget::editImagesAction()
{
    SpriteImageDialog dialog(_model->getProject()->getCurrentSprite()->getImages());
    if (dialog.exec())
    {
        _model->getProject()->getCurrentSprite()->setImages(dialog.getImages());
        _model->getProject()->getCurrentSprite()->setSelectedImage(dialog.getSelected());
        drawSprites();
    }
}

void SpritesWidget::moveUpAction()
{
    _model->getProject()->moveSpriteUp();
    drawSprites();
}

void SpritesWidget::moveDownAction()
{
    _model->getProject()->moveSpriteDown();
    drawSprites();
}

void SpritesWidget::update()
{
    if (_model->getProject()->getCurrentSprite() == NULL)
        return;

    _listWidget->setCurrentRow(_model->getProject()->getCurrentSpriteIndex());
    QListWidgetItem* item = _listWidget->item(_model->getProject()->getCurrentSpriteIndex());

    if (item != NULL)
        item->setText(_model->getProject()->getCurrentSprite()->getName());
}
