#ifndef FALSECONSTANTBLOCKREPR_H
#define FALSECONSTANTBLOCKREPR_H

#include "../blockrepr.h"

/**
 * @brief The FalseConstantBlockRepr class
 *
 * @author Brent Chesny
 */
class FalseConstantBlockRepr : public BlockRepr
{
    Q_OBJECT
public:
    FalseConstantBlockRepr(bool locked = false);

    FalseConstantBlockRepr(const FalseConstantBlockRepr& block);

    virtual BlockRepr* copy();
};

#endif // FALSECONSTANTBLOCKREPR_H
