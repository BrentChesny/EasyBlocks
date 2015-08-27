#include "trueconstantblockrepr.h"

TrueConstantBlockRepr::TrueConstantBlockRepr(bool locked)
    : BlockRepr(Block::BOOLEAN_EXPRESSION, QString("true"), locked, false)
{

}

TrueConstantBlockRepr::TrueConstantBlockRepr(const TrueConstantBlockRepr &block)
    : BlockRepr(Block::BOOLEAN_EXPRESSION, QString("true"), block.isLocked(), false)
{
}

BlockRepr* TrueConstantBlockRepr::copy()
{
    return new TrueConstantBlockRepr(*this);
}
