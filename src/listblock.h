#ifndef LISTBLOCK_H
#define LISTBLOCK_H

#include "block.h"

/**
 * @brief The ListBlock class
 *
 * @author Brecht Vandevoort
 */
class ListBlock : public Block
{
public:
    /**
     * @brief Constructor
     */
    ListBlock(const QString& listName, Value::DataType dataType) : _listName(listName), _dataType(dataType) {}

    /**
     * @brief Destructor
     */
    virtual ~ListBlock() {}

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("ListBlock");}

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
     * @brief Returns the number of bodies of the block
     * @return The number of bodies of the block
     */
    virtual int getNumBodies() const {return 0;}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QString("");}

    /**
     * @brief Returns a description of the bodies
     * @return A description of the bodies
     */
    virtual QString getBodiesDescription() const {return QString("");}

    /**
     * @brief Executes the next step of the block. This function is assumed to do an atomic step in execution, and may not execute infinitely
     * Calling this function on an instance of ListBlock doesn't do anything
     * @param executionThread The ExecutionThread this block is running on
     */
    virtual void executeNextStep(ExecutionThread& executionThread) const;

    /**
     * @brief Returns the value at a given position in the list
     * @param position The position in the list to get the value from
     * @param varTable The VarTable containing the list
     * @return Value at the given position in the list, or NULL if the position is invalid
     */
    virtual Value* getValAt(int position, const VarTable& varTable) const;

    /**
     * @brief Sets the value at a given position in the list
     * @param value The value to set
     * @param position The position in the list to set the value
     * @param varTable The VarTable containing the list
     */
    virtual void setValAt(Value* value, int position, const VarTable& varTable) const;

    /**
     * @brief Adds a value at the end of the list
     * @param value The value to add
     * @param varTable The VarTable containing the list
     */
    virtual void addValue(Value* value, const VarTable& varTable) const;

    /**
     * @brief Returns the number of items in the list
     * @param varTable The VarTable containing the list
     * @return The number of values in the list
     */
    virtual int getSize(const VarTable& varTable) const;

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
    virtual Block* newInstance() const {return new ListBlock(_listName, _dataType);}

    /**
     * @brief Returns the name of the list
     * @return Name of the list this block represents
     */
    virtual QString getListName() const {return _listName;}

private:
    QString _listName;
    Value::DataType _dataType;
};

#endif // LISTBLOCK_H
