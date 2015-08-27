#include "spritevartable.h"

SpriteVarTable::SpriteVarTable(SimpleVarTable *globals) : _globalVars(globals)
{
    _spriteVars = new SimpleVarTable;
}

SpriteVarTable::~SpriteVarTable()
{
    delete _spriteVars;
}

Value* SpriteVarTable::getValue(QString name) const
{
    Value* val = _spriteVars->getValue(name);

    if (val == NULL)
        val = _globalVars->getValue(name);

    return val;
}

bool SpriteVarTable::setValue(QString name, Value* value)
{
    bool result = _spriteVars->setValue(name, value);

    if (!result)
        result = _globalVars->setValue(name, value);

    return result;
}

void SpriteVarTable::addVariable(Variable* variable)
{
    _spriteVars->addVariable(variable);
}

Variable *SpriteVarTable::getVariable(QString name) const
{
    Variable* var = _spriteVars->getVariable(name);

    if(var == NULL)
        var = _globalVars->getVariable(name);

    return var;
}

ValueList* SpriteVarTable::getList(QString name) const
{
    ValueList* list = _spriteVars->getList(name);

    if (list == NULL)
        list = _globalVars->getList(name);

    return list;
}

void SpriteVarTable::addList(ValueList* list)
{
    _spriteVars->addList(list);
}


VarTable* SpriteVarTable::copy()
{
    SpriteVarTable* vartable = new SpriteVarTable((SimpleVarTable*) _globalVars->copy());
    vartable->setSpriteVars((SimpleVarTable*) _spriteVars->copy());
    return vartable;
}
