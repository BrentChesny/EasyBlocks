#include "simplevartable.h"

SimpleVarTable::SimpleVarTable()
{

}

SimpleVarTable::~SimpleVarTable()
{
    qDeleteAll(_lists);
    qDeleteAll(_variables);
}

Value* SimpleVarTable::getValue(QString name) const
{
    // find variable with name
    foreach (Variable* var, _variables) {
        if (var->getName() == name)
            return var->getValue();
    }

    return NULL;
}

bool SimpleVarTable::setValue(QString name, Value* value)
{
    // find variable with name
    foreach (Variable* var, _variables) {
        if (var->getName() == name) {
            var->setValue(value);
            return true;
        }
    }

    return false;
}

void SimpleVarTable::addVariable(Variable* variable)
{
    // check if there already is a variable with the same name
    foreach (Variable* var, _variables) {
        if (var->getName() == variable->getName())
            return;
    }

    _variables.append(variable);
}

Variable *SimpleVarTable::getVariable(QString name) const
{
    foreach (Variable* var, _variables) {
        if (var->getName() == name)
            return var;
    }

    return NULL;
}

ValueList* SimpleVarTable::getList(QString name) const
{
    // find list with name
    foreach (ValueList* list, _lists) {
        if (list->getName() == name)
            return list;
    }

    return NULL;
}

void SimpleVarTable::addList(ValueList* list)
{
    // check if there already is a list with the same name
    foreach (ValueList* l, _lists) {
        if (l->getName() == list->getName())
            return;
    }

    _lists.append(list);
}


VarTable* SimpleVarTable::copy()
{
    SimpleVarTable* vartable = new SimpleVarTable;

    foreach (Variable* var, _variables) {
        vartable->addVariable(var->copy());
    }

    foreach (ValueList* list, _lists) {
        vartable->addList(list->copy());
    }

    return vartable;
}
