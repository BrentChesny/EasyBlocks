#include "numberconstantblockreprview.h"

#include <QDebug>
#include <climits>

#include "../blockrepr/constantblockrepr.h"

NumberConstantBlockReprView::NumberConstantBlockReprView(ConstantBlockRepr *blockRepr, QGraphicsItem *parent)
    : BlockReprView(blockRepr, parent), _constantBlockRepr(blockRepr)
{

    //qDebug() << "nieuwe StringConstantBlockReprView aangemaakt, gebaseerd op " << blockRepr;

    QFont font("Arial", 11);
    font.setPixelSize(11);
    _lineEdit = new QLineEdit(QString::number(_constantBlockRepr->getValue().toDouble()));
    _lineEdit->setFont(font);
    _lineEdit->resize(60, 17);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::transparent);
    _lineEdit->setPalette(palette);
    _lineEdit->setAutoFillBackground(false);
    _validator = new QDoubleValidator(INT_MIN, INT_MAX, 4, this);
    _validator->setNotation(QDoubleValidator::StandardNotation);
    _lineEdit->setValidator(_validator);
    _proxy = new QGraphicsProxyWidget;
    _proxy->setWidget(_lineEdit);
    _proxy->setPos(BlockRepr::MARGIN_HORIZONTAL*2, BlockRepr::MARGIN);
    _proxy->setParentItem(this);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(numberChanged()));
}

void NumberConstantBlockReprView::numberChanged()
{
    _constantBlockRepr->setValue(QVariant(_lineEdit->text().toDouble()));
}
