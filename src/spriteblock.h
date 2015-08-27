#ifndef SPRITEBLOCK_H
#define SPRITEBLOCK_H

#include "block.h"
#include "sprite.h"

/**
 * @brief The SpriteBlock class
 *
 * @author Brecht Vandevoort
 */
class SpriteBlock : public Block
{
public:
    /**
     * @brief Constructor
     */
    SpriteBlock(Sprite *sprite);

    /**
     * @brief Destructor
     */
    virtual ~SpriteBlock() {}

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("SpriteBlock");}

    /**
     * @brief Returns the returntype of the block
     * @return The return type of the block
     */
    virtual ParamType getReturnType() const {return Block::SPRITE;}

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    /**
     * @brief Returns the number of bodies of the block
     * @return The number of bodies of the block
     */
    virtual int getNumBodies() const {return 0;}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QString("");}

    /**
     * @brief Returns a description of the bodies
     * @return A description of the bodies
     */
    virtual QString getBodiesDescription() const {return QString("");}

    /**
     * @brief Executes the next step of the block. This function is assumed to do an atomic step in execution, and may not execute infinitely
     * @param executionThread The ExecutionThread this block is running on
     */
    virtual void executeNextStep(ExecutionThread& executionThread) const;

    /**
     * @brief Adds a parameterBlock to this Block
     * @param parameter The block to add
     * @param index The index of the parameter
     * @return True if adding succeeded , false if not
     */
    virtual bool addParameter(Block* parameter, int index) {return false;}

    /**
     * @brief Adds a body to this block
     * @param body The block to add
     * @param index The index of the body
     * @return True if adding succeeded, false if not
     */
    virtual bool addBody(StatementBlock* body, int index) {return false;}

    /**
     * @brief Creates a new instance of the block and returns it
     * @return A new instance of the block
     */
    virtual Block* newInstance() const {return new SpriteBlock(_sprite);}

    /**
     * @brief Returns the sprite
     * @return Pointer to the Sprite
     */
    Sprite* getSprite() const {return _sprite;}

private:
    Sprite* _sprite;
};

#endif // SPRITEBLOCK_H
