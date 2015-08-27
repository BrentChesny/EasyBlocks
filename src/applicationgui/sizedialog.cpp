#include "sizedialog.h"

#include <QGridLayout>
#include <QKeyEvent>
#include <QIntValidator>

SizeDialog::SizeDialog(QSize* size, QWidget *parent) :
    QDialog(parent), _size(size)
{
    setWindowTitle(tr("Screen Size"));
    QGridLayout* layout = new QGridLayout(this);
    setLayout(layout);

    _heightLabel = new QLabel(tr("Height") + QString(":"));
    _heightLabel->setAlignment(Qt::AlignRight);
    _heightEdit = new QLineEdit();
    _heightEdit->setValidator( new QIntValidator(0, 1080, this) );
    _widthLabel = new QLabel(tr("Width") + QString(":"));
    _widthLabel->setAlignment(Qt::AlignRight);
    _widthEdit = new QLineEdit();
    _widthEdit->setValidator( new QIntValidator(0, 1920, this) );

    if (size != NULL)
    {
        _heightEdit->setText(QString::number(size->height()));
        _widthEdit->setText(QString::number(size->width()));
    }

    _buttons = new QDialogButtonBox;
    _buttons->addButton(QDialogButtonBox::Ok);
    _buttons->addButton(QDialogButtonBox::Cancel);

    connect(_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(_buttons, SIGNAL(rejected()), this, SLOT(reject()));

    layout->addWidget(_heightLabel, 0, 0);
    layout->addWidget(_heightEdit, 0, 1);
    layout->addWidget(_widthLabel, 1, 0);
    layout->addWidget(_widthEdit, 1, 1);
    layout->addWidget(_buttons, 2, 0, 1, 2, Qt::AlignRight);

}

void SizeDialog::accept()
{
    _size->setHeight(_heightEdit->text().toInt());
    _size->setWidth(_widthEdit->text().toInt());
    QDialog::accept();
}

void SizeDialog::keyPressEvent(QKeyEvent *evt)
{
    if(evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
        accept();
    QDialog::keyPressEvent(evt);
}
