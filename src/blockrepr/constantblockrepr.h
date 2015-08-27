#ifndef CONSTANTBLOCKREPR_H
#define CONSTANTBLOCKREPR_H

#include <QVariant>

#include "../blockrepr.h"

/**
 * @brief The ConstantBlockRepr class
 *
 * @author Brecht Vandevoort
 */
class ConstantBlockRepr : public BlockRepr
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param returnType returnType of this Block
     * @param _isLocked If true, no changes are allowed
     */
    ConstantBlockRepr(Block::ParamType returnType, bool locked = false);

    ConstantBlockRepr(const ConstantBlockRepr& block);

    virtual BlockRepr* copy();

    virtual bool isConstantBlockRepr() const { return true; }

    /**
     * @brief Returns the value of the block
     * @return The value of the block
     */
    QVariant getValue() const {return _value;}

    /**
     * @brief Sets the value
     * @param value The value to set
     */
    void setValue(QVariant value) {_value = value; emitBlockUpdated(true, true, true); }

    /**
     * @brief Returns the total size of the block
     * @return The total size of the block
     */
    virtual QSize getTotalSize();
    virtual QSize getSize();
    virtual QSize getHeaderSize();
private:
    QVariant _value;
};

#endif // CONSTANTBLOCKREPR_H
