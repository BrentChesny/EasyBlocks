#ifndef BLOCKCOLORS_H
#define BLOCKCOLORS_H

#include <QColor>

#include "../block.h"

/**
 * @brief The BlockColors class contains information about the colors of each type of block
 *
 * @author Brecht Vandevoort
 */
class BlockColors
{
public:
    static QColor getColor(Block::ParamType paramType);

private:
    BlockColors() {}
};

#endif // BLOCKCOLORS_H
