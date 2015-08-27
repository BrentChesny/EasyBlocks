#include "aliasvaluelist.h"

AliasValueList::AliasValueList(QString name, ValueList *list)
{
    _name = name;
    _alias = list;
}

AliasValueList::AliasValueList(const AliasValueList &list) : ValueList(list)
{
    _name = list.getName();
    _alias = list.getValueList();
}


