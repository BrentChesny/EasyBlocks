#include "stringconstantblockreprview.h"

#include <QDebug>

#include "../blockrepr/constantblockrepr.h"

StringConstantBlockReprView::StringConstantBlockReprView(ConstantBlockRepr *blockRepr, QGraphicsItem *parent)
    : BlockReprView(blockRepr, parent), _constantBlockRepr(blockRepr)
{
    QFont font("Arial", 11);
    font.setPixelSize(11);
    _lineEdit = new QLineEdit(_constantBlockRepr->getValue().toString());
    _lineEdit->setFont(font);
    _lineEdit->resize(60, 17);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::transparent);
    _lineEdit->setPalette(palette);
    _lineEdit->setAutoFillBackground(false);
    _proxy = new QGraphicsProxyWidget;
    _proxy->setWidget(_lineEdit);
    _proxy->setPos(BlockRepr::MARGIN_HORIZONTAL*2, BlockRepr::MARGIN);
    _proxy->setParentItem(this);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(stringChanged()));
}

void StringConstantBlockReprView::stringChanged()
{
    _constantBlockRepr->setValue(QVariant(_lineEdit->text()));
}
