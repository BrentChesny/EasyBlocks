#include "levelhandler.h"

LevelHandler::LevelHandler(bool defaultVisible) : _defaultVisible(defaultVisible)
{
}

void LevelHandler::registerVisible(const QString &id)
{
    //remove from lists if already in it
    _visible.removeAll(id);
    _invisible.removeAll(id);

    //add to list
    _visible.append(id);
}

void LevelHandler::registerInvisible(const QString &id)
{
    //remove from lists if already in it
    _visible.removeAll(id);
    _invisible.removeAll(id);

    //add to list
    _invisible.append(id);
}

bool LevelHandler::isVisible(const QString &id) const
{
    //visible
    if(_visible.contains(id))
        return true;
    //invisible
    if(_invisible.contains(id))
        return false;

    //default
    return _defaultVisible;
}
