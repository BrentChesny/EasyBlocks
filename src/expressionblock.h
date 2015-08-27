#ifndef EXPRESSIONBLOCK_H
#define EXPRESSIONBLOCK_H

#include "block.h"

/**
 * @brief The ExpressionBlock class
 *
 * @author Brecht Vandevoort
 */
class ExpressionBlock : public Block
{
public:

    /**
     * @brief Destructor
     */
    virtual ~ExpressionBlock() {}

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const = 0;

    /**
     * @brief Returns the returntype of the block
     * @return The return type of the block
     */
    virtual ParamType getReturnType() const = 0;

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const = 0;

    /**
     * @brief Returns the number of bodies of the block
     * @return The number of bodies of the block
     */
    int getNumBodies() const {return 0;}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const = 0;

    /**
     * @brief Returns a description of the bodies
     * @return A description of the bodies
     */
    QString getBodiesDescription() const {return QString("");}

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
    bool addBody(StatementBlock* body, int index) {return false;}

    /**
     * @brief Creates a new instance of the block and returns it
     * @return A new instance of the block
     */
    virtual Block* newInstance() const = 0;
};

#endif // EXPRESSIONBLOCK_H
