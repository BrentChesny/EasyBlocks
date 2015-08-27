#include "userstatementrepr.h"
#include "blockrepr/functionstartblockrepr.h"

#include <QDebug>

UserStatementRepr::UserStatementRepr(QString paramDesciption, QList<Block::ParamType> paramTypes, QStringList paramNames)
{
    _paramDescription = paramDesciption;
    _paramTypes = paramTypes;
    _paramNames = paramNames;
}

UserStatementRepr::~UserStatementRepr()
{
    qDeleteAll(_vars);
}

void UserStatementRepr::addVariable(VarBlockRepr *var)
{
    _vars.append(var);
    emit blocksUpdated();
}

void UserStatementRepr::removeVariable(VarBlockRepr *var)
{
    _vars.removeAll(var);
    emit blocksUpdated();
}

void UserStatementRepr::addStartBlock()
{
    FunctionStartBlockRepr* fsb = new FunctionStartBlockRepr();
    fsb->setPosition(QPoint(10, 10));
    addBlock(fsb);
}

