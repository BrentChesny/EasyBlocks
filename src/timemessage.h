#ifndef TIMEMESSAGE_H
#define TIMEMESSAGE_H

#include "message.h"

#include <QTime>

/**
 * @brief The TimeMessage class
 *
 * @author Brecht Vandevoort
 */
class TimeMessage : public Message
{
public:
    /**
     * @brief Constructor
     */
    TimeMessage();

    void setValue(int value) {_value = value;}

    int getValue() const {return _value;}

    /**
     * @brief Returns the stored time
     * @return The stored time
     */
    QTime getTime() const {return _time;}

    void setMillisecondsOffset(int offset);

private:
    int _value;
    QTime _time;
};

#endif // TIMEMESSAGE_H
