#include "numbervalue.h"

Value* NumberValue::copy() const
{
    NumberValue* value = new NumberValue(this->toDouble());
    return value;
}
