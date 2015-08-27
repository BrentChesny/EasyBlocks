#ifndef VALUELIST_H
#define VALUELIST_H

#include "value.h"

#include <QString>
#include <QList>

/**
 * @brief The ValueList class
 *
 * @author Brent Chesny
 */
class ValueList
{
public:
    /**
     * @brief Constructor method
     * @param name The name of the list
     * @param type The type of the list
     */
    ValueList() {}

    /**
     * @brief Copy constructor
     * @param list The list to copy
     */
    ValueList(const ValueList& list) {}

    /**
     * @brief Destructor method
     */
    virtual ~ValueList() {}

    /**
     * @brief Returns the name of the list
     * @return The name of the list
     */
    virtual QString getName() const = 0;

    /**
     * @brief Returns the value at a specific index on the list
     * @param pos The position for which to return the value
     * @return The value at position pos
     */
    virtual Value* getValueAt(int pos) const = 0;

    /**
     * @brief Sets the value at a specific index on the list
     * @param pos The position for which to set the value
     * @param value The value to set
     */
    virtual void setValueAt(int pos, Value* value) = 0;

    /**
     * @brief Adds a value to the list
     * @param value The value to add
     */
    virtual void addValue(Value* value) = 0;

    /**
     * @brief Returns the datatype
     * @return The datatype of the list
     */
    virtual Value::DataType getDataType() const = 0;

    /**
     * @brief Returns the size of a valuelist
     * @return The size of the value list
     */
    virtual int getSize() const = 0;

    /**
     * @brief Returns an exact copy of this ValueList
     * @return An exact copy of this ValueList
     */
    virtual ValueList* copy() const = 0;
};

#endif // VALUELIST_H
