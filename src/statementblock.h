#ifndef STATEMENTBLOCK_H
#define STATEMENTBLOCK_H

#include "block.h"

/**
 * @brief The StatementBlock class
 *
 * @author Brecht Vandevoort
 */
class StatementBlock : public Block
{
public:
        /**
         * @brief Destructor
         */
        virtual ~StatementBlock() {}

        /**
         * @brief Returns a unique id of the block
         * @return A unique id specific to the block
         */
        virtual QString getId() const = 0;

        /**
         * @brief Returns the returntype of the block
         * @return The return type of the block
         */
        ParamType getReturnType() const {return Block::VOID;}

        /**
         * @brief Returns a list of the paramtypes of the parameters
         * @return A QList<ParamType> containing the paramtype if each parameter
         */
        virtual QList<ParamType> getParamTypes() const = 0;

        /**
         * @brief Returns the number of bodies of the block
         * @return The number of bodies of the block
         */
        virtual int getNumBodies() const = 0;

        /**
         * @brief Returns a description of the parameters
         * @return A description of the parameters
         */
        virtual QString getParamDescription() const = 0;

        /**
         * @brief Returns a description of the bodies
         * @return A description of the bodies
         */
        virtual QString getBodiesDescription() const = 0;

        /**
         * @brief Executes the next step of the block. This function is assumed to do an atomic step in execution, and may not execute infinitely
         * @param executionThread The ExecutionThread this block is running on
         */
        virtual void executeNextStep(ExecutionThread& executionThread) const = 0;

        /**
         * @brief Adds a parameterBlock to this Block
         * @param parameter The block to add
         * @param index The index of the parameter
         * @return True if adding succeeded , false if not
         */
        virtual bool addParameter(Block* parameter, int index) = 0;

        /**
         * @brief Adds a body to this block
         * @param body The block to add
         * @param index The index of the body
         * @return True if adding succeeded, false if not
         */
        virtual bool addBody(StatementBlock* body, int index) = 0;

        /**
         * @brief Creates a new instance of the block and returns it
         * @return A new instance of the block
         */
        virtual Block* newInstance() const = 0;
};

#endif // STATEMENTBLOCK_H
