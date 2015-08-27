#include "executionthread.h"

ExecutionThread::ExecutionThread()
    : _returnValue(NULL), _keepTopBlock(true), _ioHandler(NULL)
{
}

ExecutionThread::ExecutionThread(Block *block, VarTable *varTable, Sprite *sprite, IOHandler *ioHandler)
    : _returnValue(NULL), _keepTopBlock(true), _ioHandler(ioHandler)
{
    if(block == NULL || varTable == NULL || sprite == NULL)
        return;

    ExecutionStackElement* ese = new ExecutionStackElement();
    ese->setBlock(block);
    ese->setVarTable(varTable);
    ese->setSprite(sprite);

    _executionStack.push(ese);
}

ExecutionThread::~ExecutionThread()
{
    while(!_executionStack.isEmpty())
        delete _executionStack.pop();

    if(_returnValue != NULL)
        delete _returnValue;
}

bool ExecutionThread::isEmpty() const
{
    return _executionStack.isEmpty();
}

void ExecutionThread::executeNext()
{
    //do nothing if stack is empty
    if(_executionStack.isEmpty())
        return;

    _keepTopBlock = true;
    _nextBlock = NULL;

    _executionStack.top()->getBlock()->executeNextStep(*this);

    //if top block ended execution -> pop block
    if(!_keepTopBlock)
        delete _executionStack.pop();
    //if top block did not end execution -> delete returnValue and set next block to execute
    else
    {
        if(_returnValue != NULL)
        {
            delete _returnValue;
            _returnValue = NULL;
        }

        changeTopBlock();
    }
}

void ExecutionThread::setNextBlock(Block* block)
{
    _nextBlock = block;

    //if execution stack is empty -> set block on stack immediately
    if(_executionStack.isEmpty())
        changeTopBlock();
}

void ExecutionThread::setMessage(Message* message)
{
    if(message == NULL)
        return;

    if(!_executionStack.isEmpty())
        _executionStack.top()->setMessage(message);
    else
        delete message;
}

Message* ExecutionThread::getMessage() const
{
    if(_executionStack.isEmpty())
        return NULL;

    return _executionStack.top()->getMessage();
}

void ExecutionThread::setVarTable(VarTable* varTable)
{
    if(!_executionStack.isEmpty())
        _executionStack.top()->setVarTable(varTable);
}

VarTable* ExecutionThread::getVarTable() const
{
    if(_executionStack.isEmpty())
        return NULL;

    return _executionStack.top()->getVarTable();
}

void ExecutionThread::setSprite(Sprite* sprite)
{
    if(!_executionStack.isEmpty())
        _executionStack.top()->setSprite(sprite);
}

Sprite* ExecutionThread::getSprite() const
{
    if(_executionStack.isEmpty())
        return NULL;

    return _executionStack.top()->getSprite();
}

void ExecutionThread::endExecution(Value* returnValue)
{
    if(_returnValue != NULL)
        delete _returnValue;

    _returnValue = returnValue;
    _keepTopBlock = false;
}

Value* ExecutionThread::getReturnValue() const
{
    return _returnValue;
}

void ExecutionThread::changeTopBlock()
{
    //change nothing if nextBlock is NULL or already on top
    if(_nextBlock ==NULL || (!_executionStack.isEmpty() && _executionStack.top()->getBlock() == _nextBlock))
        return;

    //create new stackElement
    ExecutionStackElement* ese;
    if(_executionStack.isEmpty())
        ese = new ExecutionStackElement();
    else
        ese = _executionStack.top()->getCopy();

    ese->setBlock(_nextBlock);

    _executionStack.push(ese);
}
