#include "userstatementblockrepr.h"

UserStatementBlockRepr::UserStatementBlockRepr(UserStatementRepr *userStatement, bool locked)
    : BlockRepr(Block::VOID, locked), _userStatement(userStatement)
{
    if(userStatement != NULL) {
        setParamTypes(userStatement->getParamTypes());
        setParamLabels(userStatement->getParamDescription());
    }
}

UserStatementBlockRepr::UserStatementBlockRepr(const UserStatementBlockRepr &userStatementBlockRepr)
    : BlockRepr(Block::VOID, userStatementBlockRepr.isLocked())
{
    _userStatement = userStatementBlockRepr._userStatement;

    if(_userStatement != NULL) {
        setParamTypes(_userStatement->getParamTypes());
        setParamLabels(_userStatement->getParamDescription());
    }
}

BlockRepr *UserStatementBlockRepr::copy()
{
    return new UserStatementBlockRepr(*this);
}
