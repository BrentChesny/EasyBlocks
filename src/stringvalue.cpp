#include "stringvalue.h"

Value* StringValue::copy() const
{
    StringValue* value = new StringValue(this->toString());
    return value;
}
