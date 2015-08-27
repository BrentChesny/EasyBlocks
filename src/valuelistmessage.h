#ifndef VALUELISTMESSAGE_H
#define VALUELISTMESSAGE_H

#include "message.h"
#include "value.h"

#include <QList>

/**
 * @brief The ValueListMessage class
 *
 * @author Brecht Vandevoort
 */
class ValueListMessage : public Message
{
public:
    /**
     * @brief Constructor
     * @param number The initial number
     */
    ValueListMessage(int number = 0) : _number(number) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueListMessage();

    /**
     * @brief Returns the current number
     * @return The number
     */
    virtual int getNumber() const {return _number;}

    /**
     * @brief Sets the number
     * @param number The number to set
     */
    virtual void setNumber(int number) {_number = number;}

    /**
     * @brief Sets the value at the given index
     * @param index The index, if less than 0, 0 is used, if greater than the current size, NULL elements are used to fill the gap
     * @param value The value to set
     */
    virtual void setValAt(int index, Value* value);

    /**
     * @brief Returns the value at the given index
     * @param index The index
     * @return Value pointer of the element at the given index
     */
    virtual Value* getValAt(int index) const {return _values.at(index);}

    /**
     * @brief Getter for the list of values
     * @return List containing Pointers to the different values
     */
    virtual QList<Value*> getValues() const {return _values;}

private:
    QList<Value*> _values;
    int _number;
};

#endif // VALUELISTMESSAGE_H
