#ifndef EXECUTIONTHREAD_H
#define EXECUTIONTHREAD_H

#include <QStack>
#include <QString>

#include "block.h"
#include "message.h"
#include "executionstackelement.h"
#include "vartable.h"
#include "sprite.h"
#include "value.h"
#include "iohandler.h"

/**
 * @brief The ExecutionThread class
 *
 * @author Brecht Vandevoort
 */
class ExecutionThread
{
public:
    /**
     * @brief Constructor
     */
    ExecutionThread();

    /**
     * @brief Constructor
     * @param block The first block to execute
     * @param varTable The vartable to use when executing the block
     * @param sprite The sprite to use when executing the block
     */
    ExecutionThread(Block* block, VarTable* varTable, Sprite* sprite, IOHandler* ioHandler);

    /**
     * @brief Destructor
     */
    ~ExecutionThread();

    /**
     * @brief Checks if the ExecutionThread has Blocks to execute
     * @return True if there are no blocks left to execute, False otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Executes the next block
     */
    void executeNext();

    /**
     * @brief Sets the next block to execute
     * @param block The next block to execute
     */
    void setNextBlock(Block* block);

    /**
     * @brief Sets the message for the block currently being executed
     * @param message The message for the current block
     */
    void setMessage(Message* message);

    /**
     * @brief Returns the message for the current block
     * @return The message for the current block
     */
    Message* getMessage() const;

    /**
     * @brief Sets the vartable for the currently executing block
     * @param varTable The vartable for the current block
     */
    void setVarTable(VarTable* varTable);

    /**
     * @brief Returns the vartable for the current block
     * @return Vartable for the current block
     */
    VarTable* getVarTable() const;

    /**
     * @brief Sets the sprite for the current block
     * @param sprite The sprite to set for the current block
     */
    void setSprite(Sprite* sprite);

    /**
     * @brief Returns the sprite for the current block
     * @return The sprite for the current block
     */
    Sprite* getSprite() const;

    /**
     * @brief An executing block needs to call this function when it wants to end his execution. (Giving execution back to the block who called this block)
     * @param returnValue The returnvalue of the block execution.
     */
    void endExecution(Value* returnValue);

    /**
     * @brief Returns the value of the last executed block
     * @return The returnvalue of the last executed block
     */
    Value* getReturnValue() const;

    /**
     * @brief Returns the IOHandler
     * @return Pointer to the IOHandler
     */
    IOHandler* getIOHandler() const {return _ioHandler;}

private:
    QStack<ExecutionStackElement*> _executionStack;
    Value* _returnValue;
    Block* _nextBlock;
    bool _keepTopBlock;
    IOHandler* _ioHandler;

    /**
     * @brief Changes the next block to be executed on the executionstack
     */
    void changeTopBlock();
};

#endif // EXECUTIONTHREAD_H
