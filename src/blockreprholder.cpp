#include "blockreprholder.h"

#include "blockrepr.h"
#include "project.h"

BlockReprHolder::BlockReprHolder()
{
}

BlockReprHolder::BlockReprHolder(const BlockReprHolder &holder) : QObject()
{
    foreach (BlockRepr* block, holder.getBlocks()) {
        BlockRepr* cpy = block->copy();
        cpy->setHolderParent(this);
        _blocks.append(cpy);
    }
}

BlockReprHolder::~BlockReprHolder()
{
    qDeleteAll(_blocks);
}

void BlockReprHolder::addBlock(BlockRepr *block)
{
    if(block != NULL) {
        _blocks.append(block);
        block->setHolderParent(this);
        emit blocksUpdated();
    }
}

bool BlockReprHolder::removeBlock(BlockRepr *block)
{
    for(int i = 0; i < _blocks.size(); i++) {
        if(_blocks[i] == block) {
            _blocks.removeAt(i);
            emit blocksUpdated();
            return true;
        }
    }

    return false;
}

void BlockReprHolder::checkExistance(Project* project)
{
    foreach (BlockRepr* b, _blocks) {
        b->checkExistance(project);
    }
}
