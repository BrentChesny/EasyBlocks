#ifndef SIMPLEVARIABLE_H
#define SIMPLEVARIABLE_H

#include "variable.h"

/**
 * @brief The SimpleVariable class
 *
 * @author Brent Chesny
 */
class SimpleVariable : public Variable
{
public:
    /**
     * @brief Constructor method
     * @param name Name of the variable
     * @param type Type of the variable
     */
    SimpleVariable(QString name, Value::DataType type, bool locked = false);

    /**
     * @brief Copy constuctor
     * @param var The variable to create a copy from
     */
    SimpleVariable(const SimpleVariable &var);

    /**
     * @brief destructor
     */
    ~SimpleVariable();

    /**
     * @brief Returns the name of the variable
     * @return The name of the variable
     */
    virtual QString getName() const { return _name; }

    /**
     * @brief Returns the value of the Variable
     * @return The value of the variable
     */
    virtual Value* getValue() const { return _value; }

    /**
     * @brief Returns the datatype of the variable
     * @return The datatype of the variable
     */
    virtual Value::DataType getDataType() const { return _dataType; }

    /**
     * @brief Sets the value for the variable, if not locked
     * @param value The value to set
     */
    virtual void setValue(Value* value);

    /**
     * @brief Sets the value for the variable, even if this variable is locked
     * @param value The value to set
     */
    void forceValue(Value* value);

    /**
     * @brief Returns an exact copy of this Variable
     * @return An exact copy of this variable
     */
    virtual Variable* copy() const { return new SimpleVariable(*this); }

private:
    /**
     * @brief The name of the variable
     */
    QString _name;

    /**
     * @brief The value of the variable
     */
    Value* _value;

    /**
     * @brief The datatype of the variable
     */
    Value::DataType _dataType;

    bool _locked;
};

#endif // SIMPLEVARIABLE_H
