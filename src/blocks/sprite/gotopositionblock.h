#ifndef GOTOPOSITIONBLOCK_H
#define GOTOPOSITIONBLOCK_H

#include "../../statementblock.h"
#include "../../expressionblock.h"

/**
 * @brief The GoToPositionBlock class
 *
 * @author Brent Chesny
 */
class GoToPositionBlock : public StatementBlock
{
public:
    /**
     * @brief Constructor
     */
    GoToPositionBlock() : _xPos(NULL), _yPos(NULL) {}

    /**
     * @brief Destructor
     */
    virtual ~GoToPositionBlock();

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("Sprite_GoToPositionBlock");}

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const;

    /**
     * @brief Returns the number of bodies of the block
     * @return The number of bodies of the block
     */
    virtual int getNumBodies() const {return 0;}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QObject::tr("Go To Position x:") + QString(" %p ") + QObject::tr("y:") + QString(" %p"); }

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
    virtual bool addParameter(Block* parameter, int index);

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
    virtual Block* newInstance() const {return new GoToPositionBlock();}

private:
    ExpressionBlock* _xPos;
    ExpressionBlock* _yPos;
};

#endif // GOTOPOSITIONBLOCK_H
