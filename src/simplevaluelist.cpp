#include "simplevaluelist.h"

SimpleValueList::SimpleValueList(QString name, Value::DataType type) : _name(name), _dataType(type)
{
}

SimpleValueList::SimpleValueList(const SimpleValueList &list) : ValueList(list)
{
    _name = list.getName();
    _dataType = list.getDataType();

    for (int i = 0; i < list.getSize(); ++i) {
        _values.append(list.getValueAt(i)->copy());
    }
}

SimpleValueList::~SimpleValueList()
{
    qDeleteAll(_values);
    _values.clear();
}

Value* SimpleValueList::getValueAt(int pos) const
{
    if (pos >= 0 && pos < _values.size())
        return _values.at(pos);

    return NULL;
}

void SimpleValueList::setValueAt(int pos, Value* value)
{
    if (value->getDataType() == _dataType && (pos >= 0 && pos < _values.size()))
    {
        if (_values.at(pos) != NULL)
            delete _values.at(pos);

        _values.replace(pos, value);
    }

}

void SimpleValueList::addValue(Value* value)
{
    if (value->getDataType() == _dataType)
        _values.append(value);
}
