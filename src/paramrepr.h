#ifndef PARAMREPR_H
#define PARAMREPR_H

#include "block.h"

class BlockRepr;

/**
 * @brief The ParamRepr class
 *
 * @author Brent Chesny
 */
class ParamRepr
{
public:
    /**
     * @brief Constructor method
     * @param type The type of the parameter
     */
    ParamRepr(Block::ParamType type);

    /**
     * @brief Destructor method
     */
    ~ParamRepr();

    /**
     * @brief Returns the current BlockRepr in the param
     * @return The block in this param
     */
    BlockRepr* getBlock() const { return _block; }

    /**
     * @brief Returns the paramtype of this parameter
     * @return The paramtype of this parameter
     */
    Block::ParamType getParamType() const { return _type; }

    /**
     * @brief Sets the blockrepr for this parameter
     * @param block The BlockRepr to set for this parameter
     */
    void setBlock(BlockRepr* block);
private:
    BlockRepr* _block;

    Block::ParamType _type;
};

#endif // PARAMREPR_H
