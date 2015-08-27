#ifndef EXECUTIONSTACKELEMENT_H
#define EXECUTIONSTACKELEMENT_H

#include "block.h"
#include "message.h"
#include "vartable.h"
#include "sprite.h"

/**
 * @brief The ExecutionStackElement class represents a single stack item in an ExecutionThread, containing a Block, a VarTable, a Sprite and a Message
 *
 * @author Brecht Vandevoort
 */
class ExecutionStackElement
{
public:
    /**
     * @brief Constructor
     */
    ExecutionStackElement() : _block(NULL), _message(NULL), _varTable(NULL), _sprite(NULL) {}

    /**
     * @brief Destructor
     */
    ~ExecutionStackElement();

    /**
     * @brief Returns the block
     * @return The block
     */
    Block* getBlock() const {return _block;}

    /**
     * @brief Sets the block
     * @param block pointer to the block to set
     */
    void setBlock(Block* block) {_block = block;}

    /**
     * @brief Returns the message
     * @return The message
     */
    Message* getMessage() const {return _message;}

    /**
     * @brief Sets the message
     * @param message The message to set
     */
    void setMessage(Message* message);

    /**
     * @brief Returns the vartable
     * @return The vartable
     */
    VarTable* getVarTable() const {return _varTable;}

    /**
     * @brief Sets the vartable
     * @param varTable The vartable to set
     */
    void setVarTable(VarTable* varTable) {_varTable = varTable;}

    /**
     * @brief Returns the sprite
     * @return The sprite
     */
    Sprite* getSprite() const {return _sprite;}

    /**
     * @brief Sets the sprite
     * @param sprite The sprite to set
     */
    void setSprite(Sprite* sprite) {_sprite = sprite;}

    /**
     * @brief Creates a copy of the current ExecutionStackElement, containing no message and the same varTable, block and sprite
     * @return
     */
    ExecutionStackElement* getCopy() const;

private:
    Block* _block;
    Message* _message;
    VarTable* _varTable;
    Sprite* _sprite;
};

#endif // EXECUTIONSTACKELEMENT_H
