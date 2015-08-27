#include "userstatement.h"

UserStatement::UserStatement(const QList<Block::ParamType> &paramTypes, const QStringList &paramNames)
    : _firstBlock(NULL)
{
    _vars = new SimpleVarTable();
    _paramTypes = paramTypes;
    _paramNames = paramNames;
}

UserStatement::~UserStatement()
{
    if(_firstBlock != NULL)
        delete _firstBlock;

    delete _vars;
}

void UserStatement::setFirstBlock(StatementBlock *firstBlock)
{
    if(_firstBlock != NULL)
        delete _firstBlock;

    _firstBlock = firstBlock;
}
