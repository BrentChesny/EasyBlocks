#include "timemessage.h"

TimeMessage::TimeMessage() : _value(0)
{
    _time = QTime::currentTime();
}

void TimeMessage::setMillisecondsOffset(int offset)
{
    _time = _time.addMSecs(offset);
}
