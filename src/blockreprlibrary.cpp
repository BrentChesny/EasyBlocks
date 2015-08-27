#include "blockreprlibrary.h"

#include "blockrepr/constantblockrepr.h"
#include "blockrepr/trueconstantblockrepr.h"
#include "blockrepr/falseconstantblockrepr.h"

BlockReprLibrary::BlockReprLibrary() : _levelHandler(NULL)
{
    //register special blocks
    registerBlock(new ConstantBlockRepr(Block::STRING_EXPRESSION, true));
    registerBlock(new ConstantBlockRepr(Block::NUMBER_EXPRESSION, true));
    registerBlock(new TrueConstantBlockRepr(true));
    registerBlock(new FalseConstantBlockRepr(true));
}

BlockReprLibrary::~BlockReprLibrary()
{
    foreach (BlockRepr* blockRepr, _blockReprs) {
        if(blockRepr != NULL)
            delete blockRepr;
    }

    _blockReprs.clear();

    if (_levelHandler != NULL)
        delete _levelHandler;
}

bool BlockReprLibrary::registerBlock(BlockRepr *blockRepr)
{
    //check if block not NULL
    if(blockRepr == NULL)
        return false;

    //check if id already in use
    if(contains(blockRepr->getId()))
        return false;

    //add block
    _blockReprs.append(blockRepr);
    return true;
}

BlockRepr* BlockReprLibrary::getBlockReprInstance(QString id) const
{
    BlockRepr* blockRepr = get(id);

    //check if block is found
    if(blockRepr == NULL)
        return NULL;
    else
        return blockRepr->copy();
}

QStringList BlockReprLibrary::createCategoryList()
{
    QStringList list;

    foreach (BlockRepr* blockRepr, _blockReprs) {
        QStringList s = blockRepr->getId().split("_");
        list.append(s.first());
    }

    list.removeDuplicates();
    list.sort();

    return list;
}

QList<BlockRepr*> BlockReprLibrary::getBlocksOfCategory(QString cat)
{
    QList<BlockRepr*> list;

    foreach (BlockRepr* blockRepr, _blockReprs) {
        QStringList s = blockRepr->getId().split("_");
        if (s.first() == cat)
            list.append(blockRepr);
    }

    return list;
}

bool BlockReprLibrary::contains(QString id)
{
    foreach (BlockRepr* blockrepr, _blockReprs) {
        if (blockrepr->getId() == id)
            return true;
    }

    return false;
}

BlockRepr* BlockReprLibrary::get(QString id) const
{
    foreach (BlockRepr* blockrepr, _blockReprs) {
        if (blockrepr->getId() == id)
            return blockrepr;
    }

    return NULL;
}

void BlockReprLibrary::setLevelHandler(LevelHandler *handler)
{
    if (_levelHandler != NULL)
        delete _levelHandler;

    _levelHandler = handler;
}

bool BlockReprLibrary::isVisible(BlockRepr *block)
{
    if (_levelHandler == NULL)
        return true;

    return _levelHandler->isVisible(block->getId());
}


