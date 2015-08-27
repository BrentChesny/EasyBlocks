#ifndef SPRITEBLOCKREPR_H
#define SPRITEBLOCKREPR_H

#include "../blockrepr.h"
#include "../spriterepr.h"

/**
 * @brief The SpriteBlockRepr class
 *
 * @author Brecht Vandevoort
 */
class SpriteBlockRepr : public BlockRepr
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param sprite The sprite this block represents
     */
    SpriteBlockRepr(SpriteRepr* sprite, bool locked = false);

    /**
     * @brief Copy constructor
     * @param spriteBlockRepr The SpriteBlockRepr to copy
     */
    SpriteBlockRepr(const SpriteBlockRepr& spriteBlockRepr);

    /**
     * @brief Creates a copy of this block
     * @return Pointer to the copy of this block
     */
    virtual BlockRepr* copy();

    /**
     * @brief Returns the SpriteRepr this block is representing
     * @return Pointer to the spriteRepr
     */
    SpriteRepr* getSpriteRepr() const {return _sprite;}

    /**
     * @brief Returns true if the block is an instance of SpriteBlockRepr
     * @return Always true, since this is an instance of SpriteBlockRepr
     */
    virtual bool isSpriteBlockRepr() const { return true; }

    /**
     * @brief Checks if this block is stil valid
     * @param project The current Project
     */
    virtual void checkExistance(Project* project);

public slots:
    /**
     * @brief This function is called when the sprite updates
     */
    void spriteUpdated();

private:
    SpriteRepr* _sprite;
};

#endif // SPRITEBLOCKREPR_H
