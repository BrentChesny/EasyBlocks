#include "paramrepr.h"
#include "blockrepr.h"

ParamRepr::ParamRepr(Block::ParamType type) : _block(NULL), _type(type)
{
}

ParamRepr::~ParamRepr()
{
    if (_block != NULL)
        delete _block;
}

void ParamRepr::setBlock(BlockRepr* block)
{
    _block = block;
}
