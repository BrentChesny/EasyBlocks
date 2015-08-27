#ifndef RANDOMBLOCK_H
#define RANDOMBLOCK_H

#include "../../expressionblock.h"

/**
 * @brief The RandomBlock class
 *
 * @author Brent Chesny
 */
class RandomBlock : public ExpressionBlock
{
public:
    /**
     * @brief Constructor
     */
    RandomBlock() : _min(NULL), _max(NULL) {}

    /**
     * @brief Destructor
     */
    virtual ~RandomBlock();

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("Number_RandomBlock");}

    /**
     * @brief Returns the returntype of the block
     * @return The return type of the block
     */
    virtual ParamType getReturnType() const {return Block::NUMBER_EXPRESSION;}

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const;

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QObject::tr("Random between %1 and %2").arg("%p", "%p"); }

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
    virtual bool addParameter(Block* parameter, int index);

    /**
     * @brief Creates a new instance of the block and returns it
     * @return A new instance of the block
     */
    virtual Block* newInstance() const {return new RandomBlock();}

private:
    ExpressionBlock* _min;
    ExpressionBlock* _max;
};

#endif // RANDOMBLOCK_H
