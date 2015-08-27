#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include <QObject>
#include <QList>

#include "signal.h"
#include "vartable.h"
#include "message.h"

class ExecutionThread;
class StatementBlock;

/**
 * @brief The Block class
 *
 * @author Brecht Vandevoort
 */
class Block
{
public:

    /**
     * @brief The ParamType enum
     */
    enum ParamType {NUMBER_EXPRESSION, STRING_EXPRESSION, BOOLEAN_EXPRESSION,
                    NUMBER_VAR, STRING_VAR, BOOLEAN_VAR,
                    NUMBER_LIST, STRING_LIST, BOOLEAN_LIST,
                    SPRITE,
                    EVENT,
                    VOID,
                    FUNCTION_START
                   };

    /**
     * @brief Destructor
     */
    virtual ~Block() {}

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

    /**
     * @brief Checks if the given ParamType is valid for the given target ParamType
     * @param given ParamType to check
     * @param target Target ParamType to match
     * @return True if the given ParamType matches the target ParamType, false if not
     */
    static bool isValidParam(ParamType given, ParamType target);

    /**
     * @brief Checks if the given paramType is an expression
     * @param paramType The ParamType to check
     * @return True if the given ParamType is an expression
     */
    static bool isExpressionParam(ParamType paramType);

    /**
     * @brief Checks if the given paramType is a variable
     * @param paramType The ParamType to check
     * @return True if the given ParamType is a variable
     */
    static bool isVariableParam(ParamType paramType);

    /**
     * @brief Checks if the given paramType is a list
     * @param paramType The ParamType to check
     * @return True if the given ParamType is a list
     */
    static bool isListParam(ParamType paramType);
};

#endif // BLOCK_H
