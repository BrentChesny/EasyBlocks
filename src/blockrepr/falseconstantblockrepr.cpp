#include "falseconstantblockrepr.h"

FalseConstantBlockRepr::FalseConstantBlockRepr(bool locked)
    : BlockRepr(Block::BOOLEAN_EXPRESSION, QString("false"), locked, false)
{

}

FalseConstantBlockRepr::FalseConstantBlockRepr(const FalseConstantBlockRepr &block)
    : BlockRepr(Block::BOOLEAN_EXPRESSION, QString("false"), block.isLocked(), false)
{
}

BlockRepr* FalseConstantBlockRepr::copy()
{
    return new FalseConstantBlockRepr(*this);
}
