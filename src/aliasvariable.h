#ifndef ALIASVARIABLE_H
#define ALIASVARIABLE_H

#include "variable.h"

/**
 * @brief The AliasVariable class
 *
 * @author Brent Chesny
 */
class AliasVariable : public Variable
{
public:
    AliasVariable(QString name, Variable *var);

    AliasVariable(const AliasVariable &var);

    /**
     * @brief Returns the name of the variable
     * @return The name of the variable
     */
    virtual QString getName() const { return _name; }

    /**
     * @brief Returns the value of the Variable
     * @return The value of the variable
     */
    virtual Value* getValue() const { return _alias->getValue(); }

    /**
     * @brief Returns the datatype of the variable
     * @return The datatype of the variable
     */
    virtual Value::DataType getDataType() const { return _alias->getDataType(); }

    /**
     * @brief Sets the value for the variable
     * @param value The value to set
     */
    virtual void setValue(Value* value) { _alias->setValue(value); }

    /**
     * @brief Returns the variable this variable is pointing to
     * @return Pointer to the variable this variable is pointing to
     */
    Variable* getVariable() const { return _alias; }

    /**
     * @brief Returns an exact copy of this Variable
     * @return An exact copy of this variable
     */
    virtual Variable* copy() const { return new AliasVariable(*this); }

private:
    QString _name;

    Variable* _alias;
};

#endif // ALIASVARIABLE_H
