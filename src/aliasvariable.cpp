#include "aliasvariable.h"

AliasVariable::AliasVariable(QString name, Variable* var) :
    _name(name), _alias(var)
{
}

AliasVariable::AliasVariable(const AliasVariable &var)
{
    _name = var.getName();
    _alias = var.getVariable();
}
