#include "booleanvalue.h"

Value* BooleanValue::copy() const
{
    BooleanValue* value = new BooleanValue(this->toBool());
    return value;
}
