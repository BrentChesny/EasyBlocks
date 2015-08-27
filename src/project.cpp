#include "project.h"
#include "compiler/projectcompiler.h"
#include <qalgorithms.h>

Project::Project() : _path(QString())
{
    _screen = new ScreenRepr;
    connect(_screen, SIGNAL(updated()), this, SLOT(sendUpdate()));
    _sprites.append(new SpriteRepr(new QPixmap(":/sprites/sprites/bee.png"), "Bee", _screen->getCenter()));
    foreach (SpriteRepr* s, _sprites) {
        connect(s, SIGNAL(graphicsUpdated()), this, SLOT(sendUpdate()));
        connect(s, SIGNAL(blocksUpdated()), this, SLOT(sendUpdate()));
    }
    foreach (UserStatementRepr* us, _userStatements) {
        connect(us, SIGNAL(blocksUpdated()), this, SLOT(sendUpdate()));
    }
    _currentSpriteIndex = 0;
    _currentFuncIndex = -1;
    _blockLibrary = new BlockLibrary;
    _blockReprLibrary = _blockLibrary->createBlockReprLibrary();
}

Project::~Project()
{
    delete _blockReprLibrary;
    delete _blockLibrary;
    delete _screen;

    qDeleteAll(_sprites);
    qDeleteAll(_vars);
    qDeleteAll(_userStatements);
    qDeleteAll(_userStatementBlockReprs);

    _sprites.clear();
    _userStatements.clear();
}

void Project::setScreen(ScreenRepr *screen)
{
    if (_screen != NULL)
        delete _screen;

    _screen = screen;
    connect(_screen, SIGNAL(updated()), this, SLOT(sendUpdate()));
}

UserStatementRepr *Project::getCurrentFunc() const
{
    if(_currentFuncIndex < 0 || _currentFuncIndex >= _userStatements.size())
        return NULL;

    return _userStatements.at(_currentFuncIndex);
}

SpriteRepr* Project::getCurrentSprite() const
{
    if (_currentSpriteIndex < 0 || _currentSpriteIndex >= _sprites.size())
        return NULL;

    return _sprites.at(_currentSpriteIndex);
}

void Project::addSprite(QPixmap* image, QString name)
{
    SpriteRepr* sprite = new SpriteRepr(image, name, _screen->getCenter());
    addSprite(sprite);
}

void Project::addSprite(SpriteRepr *sprite)
{
    if (_currentSpriteIndex == -1)
        _currentSpriteIndex = 0;

    connect(sprite, SIGNAL(graphicsUpdated()), this, SLOT(sendUpdate()));
    connect(sprite, SIGNAL(blocksUpdated()), this, SLOT(sendUpdate()));
    _sprites.append(sprite);
    sendUpdate();
}

void Project::removeSprite(int index)
{
    if (index < 0 || index > _sprites.size() - 1)
        return;

    if (index == _currentSpriteIndex)
        _currentSpriteIndex = 0;
    else if (index < _currentSpriteIndex)
        _currentSpriteIndex--;

    delete _sprites.takeAt(index);

    if (_sprites.size() == 0)
        _currentSpriteIndex = -1;

    checkExistance();
    sendUpdate();
}

void Project::moveSpriteUp()
{
    if (_currentSpriteIndex == -1)
        return;

    if (_currentSpriteIndex > 0)
    {
        _sprites.swap(_currentSpriteIndex, _currentSpriteIndex-1);
        _currentSpriteIndex--;
        sendUpdate();
    }
}

void Project::moveSpriteDown()
{
    if (_currentSpriteIndex == -1)
        return;

    if (_currentSpriteIndex < _sprites.size() - 1)
    {
        _sprites.swap(_currentSpriteIndex, _currentSpriteIndex+1);
        _currentSpriteIndex++;
        sendUpdate();
    }
}

int Project::getIndexOfSprite(SpriteRepr* sprite)
{
    int i = 0;
    foreach (SpriteRepr* s, _sprites) {
        if (s == sprite)
            return i;
        i++;
    }

    return -1;
}

void Project::addVariable(VarBlockRepr* var)
{
    _vars.append(var);
    sendUpdate();
}

void Project::removeVariable(VarBlockRepr *var)
{
    _vars.removeAll(var);
    foreach (SpriteRepr* sprite, _sprites)
        sprite->removeVariable(var);
    sendUpdate();
    checkExistance();
}

bool Project::hasVariableWithName(QString name)
{
    foreach(VarBlockRepr* var, _vars)
    {
        if (var->getVarName() == name)
            return true;
    }

    foreach (SpriteRepr* sprite, _sprites) {
        if(sprite->hasVariableWithName(name))
            return true;
    }

    return false;
}

void Project::duplicateCurrentSprite()
{
    _sprites.append(new SpriteRepr(*getCurrentSprite()));
    sendUpdate();
}

void Project::sendUpdate()
{
    emit updated();
}

Program* Project::createRunnableProgram()
{
    ProjectCompiler compiler(this);
    return compiler.compile();
}

void Project::checkExistance()
{
    foreach (SpriteRepr* s, _sprites) {
        s->checkExistance(this);
    }
}

void Project::addUserStatement(UserStatementRepr *userStatement)
{
    if(userStatement == NULL)
        return;

    _userStatements.append(userStatement);
    connect(userStatement, SIGNAL(blocksUpdated()), this, SLOT(sendUpdate()));
    sendUpdate();
}

void Project::removeUserStatement(UserStatementRepr *userStatement)
{
    _userStatements.removeAll(userStatement);
    sendUpdate();
}

QList<UserStatementBlockRepr*> Project::getUserStatementBlockReprs()
{
    if (_userStatementBlockReprs.size() > 0) {
        qDeleteAll(_userStatementBlockReprs);
        _userStatementBlockReprs.clear();
    }

    foreach (UserStatementRepr* us, _userStatements) {
        UserStatementBlockRepr* usbr = new UserStatementBlockRepr(us, true);
        _userStatementBlockReprs.append(usbr);
    }

    return _userStatementBlockReprs;
}

int Project::getIndexOfUserStatement(UserStatementRepr *us)
{
    for (int i = 0; i < _userStatements.size(); ++i) {
        if (us == _userStatements.at(i))
            return i;
    }

    return -1;
}

void Project::reloadBlockReprLibrary()
{
    delete _blockReprLibrary;
    _blockReprLibrary = _blockLibrary->createBlockReprLibrary();
}
