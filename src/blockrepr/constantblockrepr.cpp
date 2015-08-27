#include "constantblockrepr.h"

#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QDebug>

ConstantBlockRepr::ConstantBlockRepr(Block::ParamType returnType, bool locked)
    : BlockRepr(returnType, locked), _value(0)
{
    if(returnType == Block::STRING_EXPRESSION)
        _value.setValue(QString(tr("text")));
}

ConstantBlockRepr::ConstantBlockRepr(const ConstantBlockRepr& block) : BlockRepr(block.getReturnType(), block.isLocked()), _value(block.getValue())
{
}

BlockRepr* ConstantBlockRepr::copy()
{
    return new ConstantBlockRepr(*this);
}

QSize ConstantBlockRepr::getTotalSize()
{
    return getSize();
}

QSize ConstantBlockRepr::getSize()
{
    return getHeaderSize();
}

QSize ConstantBlockRepr::getHeaderSize()
{
    QFont font("Arial", 11);
    font.setPixelSize(11);
    QLineEdit* lineedit = new QLineEdit;
    lineedit->setText(_value.toString());
    lineedit->setFont(font);
    lineedit->resize(60, 17);
    lineedit->setContentsMargins(0,0,0,0);
    QGraphicsProxyWidget proxy;
    proxy.setWidget(lineedit);

    return QSize(proxy.boundingRect().size().toSize().width(), proxy.boundingRect().size().toSize().height() - 4) + QSize(MARGIN_HORIZONTAL * 4, MARGIN *2);
}
