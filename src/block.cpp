#include "block.h"

#include "executionthread.h"


bool Block::isValidParam(Block::ParamType given, Block::ParamType target)
{
    //if equal -> match
    if(given == target)
        return true;

    //if given is a Variable and target is an Expression -> match
    if(given == BOOLEAN_VAR && target == BOOLEAN_EXPRESSION)
        return true;
    if(given == NUMBER_VAR && target == NUMBER_EXPRESSION)
        return true;
    if(given == STRING_VAR && target == STRING_EXPRESSION)
        return true;

    //if none of the above -> no match
    return false;
}

bool Block::isExpressionParam(Block::ParamType paramType)
{
    return (paramType == BOOLEAN_EXPRESSION
            || paramType == NUMBER_EXPRESSION
            || paramType == STRING_EXPRESSION);
}

bool Block::isVariableParam(Block::ParamType paramType)
{
    return (paramType == BOOLEAN_VAR
            || paramType == NUMBER_VAR
            || paramType == STRING_VAR);
}

bool Block::isListParam(Block::ParamType paramType)
{
    return (paramType == BOOLEAN_LIST
            || paramType == NUMBER_LIST
            || paramType == STRING_LIST);
}
