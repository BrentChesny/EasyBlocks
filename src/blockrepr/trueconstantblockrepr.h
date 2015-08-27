#ifndef TRUECONSTANTBLOCKREPR_H
#define TRUECONSTANTBLOCKREPR_H

#include "../blockrepr.h"

/**
 * @brief The TrueConstantBlockRepr class
 *
 * @author Brecht Vandevoort
 */
class TrueConstantBlockRepr : public BlockRepr
{
    Q_OBJECT
public:
    TrueConstantBlockRepr(bool locked = false);

    TrueConstantBlockRepr(const TrueConstantBlockRepr& block);

    virtual BlockRepr* copy();
};

#endif // TRUECONSTANTBLOCKREPR_H
