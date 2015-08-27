#ifndef VARIABLE_H
#define VARIABLE_H

#include "value.h"

#include <QString>

/**
 * @brief The Variable class
 *
 * @author Brent Chesny
 */
class Variable
{
public:
    /**
     * @brief Constructor method
     * @param name Name of the variable
     * @param type Type of the variable
     */
    Variable() {}

    /**
     * @brief Destructor method
     */
    virtual ~Variable() {}

    /**
     * @brief Returns the name of the variable
     * @return The name of the variable
     */
    virtual QString getName() const = 0;

    /**
     * @brief Returns the value of the Variable
     * @return The value of the variable
     */
    virtual Value* getValue() const = 0;

    /**
     * @brief Returns the datatype of the variable
     * @return The datatype of the variable
     */
    virtual Value::DataType getDataType() const = 0;

    /**
     * @brief Sets the value for the variable
     * @param value The value to set
     */
    virtual void setValue(Value* value) = 0;

    /**
     * @brief Returns an exact copy of this Variable
     * @return An exact copy of this variable
     */
    virtual Variable* copy() const = 0;
};

#endif // VARIABLE_H
