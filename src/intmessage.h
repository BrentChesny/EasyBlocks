#ifndef INTMESSAGE_H
#define INTMESSAGE_H

#include "message.h"

/**
 * @brief The IntMessage class
 *
 * @author Brecht Vandevoort
 */
class IntMessage : public Message
{
public:
    /**
     * @brief Constructor
     */
    IntMessage(int value = 0) : _value(value) {}

    /**
     * @brief Sets the value
     * @param value The value to set
     */
    void setValue(int value) {_value = value;}

    /**
     * @brief Returns the current value
     * @return The current value
     */
    int getValue() const {return _value;}

private:
    int _value;
};

#endif // INTMESSAGE_H
