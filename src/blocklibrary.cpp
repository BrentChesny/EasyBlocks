#include "blocklibrary.h"

#include "blockreprlibrary.h"
#include "blocks/blocks.h"

BlockLibrary::BlockLibrary()
{
    //register blocks
    registerBlock(new IfBlock());
    registerBlock(new IfElseBlock());
    registerBlock(new WaitUntilBlock());
    registerBlock(new WaitSecondsBlock());
    registerBlock(new StartBlock());
    registerBlock(new MouseClickBlock());
    registerBlock(new ArrowUpBlock());
    registerBlock(new ArrowDownBlock());
    registerBlock(new ArrowLeftBlock());
    registerBlock(new ArrowRightBlock());
    registerBlock(new EnterBlock());
    registerBlock(new SpaceBlock());
    registerBlock(new WhileBlock());
    registerBlock(new RepeatXBlock());
    registerBlock(new NumberAssignment());
    registerBlock(new PlusBlock());
    registerBlock(new MinusBlock());
    registerBlock(new MultiplyBlock());
    registerBlock(new DivideBlock());
    registerBlock(new RandomBlock());
    registerBlock(new EqualNumberBlock());
    registerBlock(new LessThanNumberBlock());
    registerBlock(new GreaterThanNumberBlock());
    registerBlock(new NextImageBlock());
    registerBlock(new RotateSpriteBlock());
    registerBlock(new GoToPositionBlock());
    registerBlock(new GoToSpriteBlock());
    registerBlock(new MoveStepsBlock());
    registerBlock(new CollidesSpriteBlock());
    registerBlock(new BounceEdgeBlock());
    registerBlock(new BoolAssignmentBlock());
    registerBlock(new LogicalAndBlock());
    registerBlock(new LogicalOrBlock());
    registerBlock(new LogicalNotBlock());
    registerBlock(new SetInvisibleBlock());
    registerBlock(new SetVisibleBlock());
    registerBlock(new ResizeBlock());
    registerBlock(new ResizeToBlock());
    registerBlock(new SpriteHeightBlock());
    registerBlock(new SpriteWidthBlock());
    registerBlock(new SpriteRotationBlock());
    registerBlock(new SpriteXPosBlock());
    registerBlock(new SpriteYPosBlock());
    registerBlock(new SpriteVisibleBlock());
    registerBlock(new StringAssignmentBlock());
    registerBlock(new ConcatenateBlock());
    registerBlock(new CharAtBlock());
    registerBlock(new LengthBlock());
    registerBlock(new EqualBoolBlock());
    registerBlock(new EqualStringBlock());
    registerBlock(new PrintBlock());
    registerBlock(new AskBlock());
    registerBlock(new NumberFromListBlock());
    registerBlock(new AddNumberToListBlock());
    registerBlock(new AppendNumberToList());
    registerBlock(new ConvertNumberToStringBlock());
    registerBlock(new NumberListSize());
    registerBlock(new MessageSignalReceivedBlock());
    registerBlock(new SendMessageSignalToSpriteBlock());
}

BlockLibrary::~BlockLibrary()
{
    foreach (Block* block, _blocks) {
        if(block != NULL)
            delete block;
    }

    _blocks.clear();
}

bool BlockLibrary::registerBlock(Block* block)
{
    //check if block not NULL
    if(block == NULL)
        return false;

    //check if id already in use
    if(contains(block->getId()))
        return false;

    //add block
    _blocks.append(block);
    return true;
}

Block* BlockLibrary::getBlockInstance(QString id) const
{
    Block* block = get(id);

    //check if block is found
    if(block == NULL)
        return NULL;
    else
        return block->newInstance();
}

BlockReprLibrary* BlockLibrary::createBlockReprLibrary() const
{
    BlockReprLibrary* lib = new BlockReprLibrary;

    foreach (Block* block, _blocks) {
        lib->registerBlock(new BlockRepr(block, true));
    }

    return lib;
}

bool BlockLibrary::contains(QString id)
{
    foreach (Block* block, _blocks) {
        if (block->getId() == id)
            return true;
    }

    return false;
}

Block *BlockLibrary::get(QString id) const
{
    foreach (Block* block, _blocks) {
        if (block->getId() == id)
            return block;
    }

    return NULL;
}
