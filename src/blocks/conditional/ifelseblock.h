#ifndef IFELSEBLOCK_H
#define IFELSEBLOCK_H

#include "../../statementblock.h"
#include "../../expressionblock.h"

/**
 * @brief The IfElseBlock class
 *
 * @author Brent Chesny
 */
class IfElseBlock : public StatementBlock
{
public:
    /**
     * @brief Constructor method
     */
    IfElseBlock() : _condition(NULL), _ifBody(NULL), _elseBody(NULL) {}

    /**
     * @brief Destructor method
     */
    virtual ~IfElseBlock();

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("Control_IfElseBlock");}

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const;

    /**
     * @brief Returns the number of bodies of the block
     * @return The number of bodies of the block
     */
    virtual int getNumBodies() const {return 2;}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QObject::tr("If") + QString(" %p");}

    /**
     * @brief Returns a description of the bodies
     * @return A description of the bodies
     */
    virtual QString getBodiesDescription() const {return QObject::tr("Then") + QString(" %b ") + QObject::tr("Else") + QString(" %b");}

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
     * @brief Adds a body to this block
     * @param body The block to add
     * @param index The index of the body
     * @return True if adding succeeded, false if not
     */
    virtual bool addBody(StatementBlock* body, int index);

    /**
     * @brief Creates a new instance of the block and returns it
     * @return A new instance of the block
     */
    virtual Block* newInstance() const {return new IfElseBlock();}

private:
    ExpressionBlock* _condition;
    StatementBlock* _ifBody;
    StatementBlock* _elseBody;
};

#endif // IFELSEBLOCK_H
