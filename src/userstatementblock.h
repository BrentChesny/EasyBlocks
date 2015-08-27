#ifndef USERSTATEMENTBLOCK_H
#define USERSTATEMENTBLOCK_H

#include "statementblock.h"
#include "userstatement.h"
#include "valuelistmessage.h"

/**
 * @brief The UserStatementBlock class
 *
 * @author Brecht Vandevoort
 */
class UserStatementBlock : public StatementBlock
{
public:
    /**
     * @brief Constructor
     * @param userStatement Pointer to the UserStatement this block represents
     */
    UserStatementBlock(UserStatement* userStatement);

    /**
     * @brief Destructor
     */
    virtual ~UserStatementBlock();

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("UserStatement");}

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
    virtual QString getParamDescription() const;

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
    virtual Block* newInstance() const {return new UserStatementBlock(_userStatement);}

private:
    /**
     * @brief Pointer to the UserStatement this block represents
     */
    UserStatement* _userStatement;

    /**
     * @brief Array of Block* containing the different parameters
     */
    Block** _params;
    int _paramsSize;

    /**
     * @brief Evaluates a param if it is an expression
     * @param index Index of the param to evaluate
     * @param executionThread The executionThread
     * @param message The ValueListMessage
     */
    void evaluateParam(int index, ExecutionThread& executionThread, ValueListMessage* message) const;

    /**
     * @brief Stores the parameter if it is an expression, assuming it executed before calling this function
     * @param index index of the param
     * @param executionThread The ExecutionThread
     * @param message The ValueListMessage
     */
    void storeParam(int index, ExecutionThread& executionThread, ValueListMessage* message) const;

    /**
     * @brief Prepares the UserStatement for execution in the current executionThread
     * @param executionThread The ExecutionThread
     * @param message The ValueListMessage
     */
    void runUserStatement(ExecutionThread& executionThread, ValueListMessage* message) const;

    /**
     * @brief Converts a ParamType to the equivalent DataType
     * @return DataType of the given ParamType
     */
    Value::DataType toDataType(Block::ParamType paramType) const;
};

#endif // USERSTATEMENTBLOCK_H
