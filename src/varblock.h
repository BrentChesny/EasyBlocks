#ifndef VARBLOCK_H
#define VARBLOCK_H

#include "expressionblock.h"

/**
 * @brief The VarBlock class
 */
class VarBlock : public ExpressionBlock
{
public:

    /**
     * @brief Constructor
     * @param varName Name of the variable
     * @param dataType datatype of the variable
     */
    VarBlock(const QString& varName, Value::DataType dataType) : _varName(varName), _dataType(dataType) {}

    /**
     * @brief Destructor
     */
    virtual ~VarBlock() {}

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("VarBlock");}

    /**
     * @brief Returns the returntype of the block
     * @return The return type of the block
     */
    virtual ParamType getReturnType() const;

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QString("");}

    /**
     * @brief Executes the next step of the block. This function is assumed to do an atomic step in execution, and may not execute infinitely
     * @param executionThread The ExecutionThread this block is running on
     */
    virtual void executeNextStep(ExecutionThread& executionThread) const;

    /**
     * @brief Sets the value of the variable represented by this block by looking it up in the given varTable.
     * If the variable is not found, or if the value hasn't the correct DataType, nothing will happen
     * @param value The value to change the variable to
     * @param varTable The VarTable containing the variable to change
     */
    virtual void setValue(Value* value, VarTable& varTable) const;

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
    virtual Block* newInstance() const {return new VarBlock(_varName, _dataType);}

    /**
     * @brief Returns the name of the variable
     * @return Name of the variable
     */
    virtual QString getVarName() const {return _varName;}

private:
    QString _varName;
    Value::DataType _dataType;
};

#endif // VARBLOCK_H
