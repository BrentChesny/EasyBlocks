#ifndef VALUEMESSAGE_H
#define VALUEMESSAGE_H

#include "message.h"
#include "value.h"

/**
 * @brief The ValueMessage class, This message contains an int and a Value pointer
 *
 * @author Brecht Vandevoort
 */
class ValueMessage : public Message
{
public:
    /**
     * @brief Constructor
     * @param value The initial value
     * @param number The initial number
     */
    ValueMessage(Value* value = NULL, int number = 0) : _value(value), _number(number) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueMessage();

    /**
     * @brief Returns the current value
     * @return The Value pointer
     */
    virtual Value* getValue() const {return _value;}

    /**
     * @brief Sets the value
     * @param value Pointer to the value to set
     */
    virtual void setValue(Value* value);

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

private:
    Value* _value;
    int _number;

};

#endif // VALUEMESSAGE_H
