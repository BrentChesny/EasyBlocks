#ifndef SIMPLEVALUELIST_H
#define SIMPLEVALUELIST_H

#include "valuelist.h"

/**
 * @brief The SimpleValueList class
 *
 * @author Brent Chesny
 */
class SimpleValueList : public ValueList
{
public:
    SimpleValueList(QString name, Value::DataType type);
    SimpleValueList(const SimpleValueList &list);

    virtual ~SimpleValueList();

    /**
     * @brief Returns the name of the list
     * @return The name of the list
     */
    QString getName() const { return _name; }

    /**
     * @brief Returns the value at a specific index on the list
     * @param pos The position for which to return the value
     * @return The value at position pos
     */
    Value* getValueAt(int pos) const;

    /**
     * @brief Sets the value at a specific index on the list
     * @param pos The position for which to set the value
     * @param value The value to set
     */
    void setValueAt(int pos, Value* value);

    /**
     * @brief Adds a value to the list
     * @param value The value to add
     */
    void addValue(Value* value);

    /**
     * @brief Returns the datatype
     * @return The datatype of the list
     */
    Value::DataType getDataType() const { return _dataType; }

    /**
     * @brief Returns the size of a valuelist
     * @return The size of the value list
     */
    int getSize() const { return _values.size(); }

    /**
     * @brief Returns an exact copy of this ValueList
     * @return An exact copy of this ValueList
     */
    ValueList *copy() const {return new SimpleValueList(*this);}

private:
    /**
     * @brief The name of the list
     */
    QString _name;

    /**
     * @brief The values in the list
     */
    QList<Value*> _values;

    /**
     * @brief The datatype of the list
     */
    Value::DataType _dataType;
};

#endif // SIMPLEVALUELIST_H
