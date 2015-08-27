#include "simplevariable.h"

#include "numbervalue.h"
#include "stringvalue.h"
#include "booleanvalue.h"

SimpleVariable::SimpleVariable(QString name, Value::DataType type, bool locked) : _name(name), _dataType(type), _locked(locked)
{
    if (type == Value::NUMBER)
        _value = new NumberValue(0.0);
    else if (type == Value::STRING)
        _value = new StringValue("");
    else if (type == Value::BOOLEAN)
        _value = new BooleanValue(false);
}

SimpleVariable::SimpleVariable(const SimpleVariable &var)
{
    _name = var.getName();
    _dataType = var.getDataType();
    _value = var.getValue()->copy();
    _locked = var._locked;
}

SimpleVariable::~SimpleVariable()
{
    if(_value != NULL)
        delete _value;
}

void SimpleVariable::setValue(Value *value)
{
    if (_locked || value->getDataType() != _dataType) {
        if(value != NULL)
            delete value;
        return;
    }

    if (_value != NULL)
        delete _value;

    _value = value;
}

void SimpleVariable::forceValue(Value *value)
{
    if (value->getDataType() != _dataType)
        return;

    if (_value != NULL)
        delete _value;

    _value = value;
}
