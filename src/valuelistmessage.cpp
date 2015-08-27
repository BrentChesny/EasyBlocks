#include "valuelistmessage.h"



ValueListMessage::~ValueListMessage()
{
    foreach (Value* v, _values) {
        if(v != NULL)
            delete v;
    }
}

void ValueListMessage::setValAt(int index, Value *value)
{
    if(index < 0)
        index  = 0;

    //fill list to append element
    if(index >= _values.size()) {
        while(index > _values.size())
            _values.append(NULL);

        _values.append(value);
    }

    //replace element
    else {
        if(_values.at(index) != NULL)
            delete _values.at(index);
        _values.replace(index, value);
    }
}
