#include "eventblock.h"
#include "statementblock.h"

EventBlock::~EventBlock()
{
    if(_statement != NULL)
        delete _statement;
}
