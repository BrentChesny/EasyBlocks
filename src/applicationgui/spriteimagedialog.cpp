#include "spriteimagedialog.h"
#include "ui_spriteimagedialog.h"

#include <QDebug>
#include <QFileDialog>


SpriteImageDialog::SpriteImageDialog(QList<QPixmap *> images, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpriteImageDialog),
    _images(images)
{
    _scene = new QGraphicsScene;
    _scene->setBackgroundBrush(Qt::transparent);
    ui->setupUi(this);
    ui->preview->setScene(_scene);
    ui->preview->setFixedWidth(150);
    ui->preview->setStyleSheet( "QGraphicsView { border-style: none; background: transparent; }" );
    ui->preview->setScene(_scene);
    ui->imagesList->setFocusPolicy(Qt::NoFocus);
    ui->imagesList->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->imagesList, SIGNAL(currentRowChanged(int)), this, SLOT(rowSelectionChanged(int)));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addImage()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(removeImage()));

    _current = 0;
    update();

    setWindowTitle(tr("Sprite Images"));
}

SpriteImageDialog::~SpriteImageDialog()
{
    delete ui;
    delete _scene;
}

void SpriteImageDialog::update()
{
    fillList();
    drawPreview();
}

void SpriteImageDialog::addImage()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Files"), QDir::currentPath(), tr("*.jpg *.png"));

    if (!path.isNull())
    {
        QPixmap* image = new QPixmap(path);
        if (!image->isNull())
        {
            _images.append(image);
            update();
        }
    }

    if(_images.size() > 1)
        ui->removeBtn->setEnabled(true);
}

void SpriteImageDialog::removeImage()
{
    //ignore if only 1 item in the list
    if(_images.size() <= 1)
        return;

    _images.removeAt(_current);
    _current--;
    if (_current < 0)
        _current = 0;
    update();

    if(_images.size() <= 1)
        ui->removeBtn->setDisabled(true);
}

void SpriteImageDialog::fillList()
{
    int current = _current;
    ui->imagesList->clear();
    for (int i = 0; i < _images.length(); i++) {
        QListWidgetItem* item = new QListWidgetItem(tr("Image") + " " + QString::number(i+1));
        ui->imagesList->addItem(item);
    }
    ui->imagesList->setCurrentRow(current);

    if(_images.size() <= 1)
        ui->removeBtn->setDisabled(true);
}

void SpriteImageDialog::drawPreview()
{
    _scene->clear();

    if (_current >= 0 && _current < _images.size())
        _scene->addPixmap(*(_images.at(_current)));
}

void SpriteImageDialog::rowSelectionChanged(int index)
{
    _current = index;
    drawPreview();
}

