#ifndef FUNCTIONSTARTBLOCKREPR_H
#define FUNCTIONSTARTBLOCKREPR_H

#include "../blockrepr.h"

/**
 * @brief The FunctionStartBlockRepr class
 *
 * @author Brecht Vandevoort
 */
class FunctionStartBlockRepr : public BlockRepr
{
public:
    /**
     * @brief Constructor
     */
    FunctionStartBlockRepr();

    /**
     * @brief Copy constructor
     * @param functionStartBlockRepr The FunctionStartBlockRepr to copy
     */
    FunctionStartBlockRepr(const FunctionStartBlockRepr& functionStartBlockRepr);

    /**
     * @brief Returns a copy of this block
     * @return A copy of this block
     */
    virtual BlockRepr *copy() {return new FunctionStartBlockRepr(*this);}
};

#endif // FUNCTIONSTARTBLOCKREPR_H
