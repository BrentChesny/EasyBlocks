#ifndef ALIASVALUELIST_H
#define ALIASVALUELIST_H

#include "valuelist.h"

class AliasValueList : public ValueList
{
public:
    AliasValueList(QString name, ValueList* list);
    AliasValueList(const AliasValueList &list);

    /**
     * @brief Returns the name of the list
     * @return The name of the list
     */
    virtual QString getName() const { return _name; }

    /**
     * @brief Returns the value at a specific index on the list
     * @param pos The position for which to return the value
     * @return The value at position pos
     */
    virtual Value* getValueAt(int pos) const { return _alias->getValueAt(pos); }

    /**
     * @brief Sets the value at a specific index on the list
     * @param pos The position for which to set the value
     * @param value The value to set
     */
    virtual void setValueAt(int pos, Value* value) { _alias->setValueAt(pos, value);}

    /**
     * @brief Adds a value to the list
     * @param value The value to add
     */
    virtual void addValue(Value* value) { _alias->addValue(value); }

    /**
     * @brief Returns the datatype
     * @return The datatype of the list
     */
    virtual Value::DataType getDataType() const { return _alias->getDataType(); }

    /**
     * @brief Returns the size of a valuelist
     * @return The size of the value list
     */
    virtual int getSize() const { return _alias->getSize(); }

    /**
     * @brief Returns the ValueList this list is pointing to
     * @return Pointer to the ValueList this ValueList is pointing to
     */
    ValueList* getValueList() const { return _alias; }

    /**
     * @brief Returns an exact copy of this ValueList
     * @return An exact copy of this ValueList
     */
    virtual ValueList* copy() const { return new AliasValueList(*this); }

private:
    QString _name;

    ValueList* _alias;
};

#endif // ALIASVALUELIST_H
