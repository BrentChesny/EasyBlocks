#include "blockcolors.h"

QColor BlockColors::getColor(Block::ParamType paramType)
{
    if(paramType == Block::VOID)
        return QColor(220, 220, 0);

    if(paramType == Block::BOOLEAN_EXPRESSION)
        return QColor(0, 230, 0);

    if(paramType == Block::BOOLEAN_VAR)
        return QColor(0, 200, 0);

    if(paramType == Block::BOOLEAN_LIST)
        return QColor(0, 170, 0);


    if(paramType == Block::NUMBER_EXPRESSION)
        return QColor(0, 200, 240);

    if(paramType == Block::NUMBER_VAR)
        return QColor(0, 170, 210);

    if(paramType == Block::NUMBER_LIST)
        return QColor(0, 140, 190);


    if(paramType == Block::STRING_EXPRESSION)
        return QColor(250, 80, 35);

    if(paramType == Block::STRING_VAR)
        return QColor(220, 70, 25);

    if(paramType == Block::STRING_LIST)
        return QColor(200, 65, 20);


    if(paramType == Block::EVENT)
        return QColor(220, 190, 10);

    if(paramType == Block::SPRITE)
        return QColor(170, 110, 70);

    return QColor(100, 100, 100);
}
