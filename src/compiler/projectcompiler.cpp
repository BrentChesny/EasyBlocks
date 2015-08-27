#include "projectcompiler.h"

#include <QMap>
#include <QDebug>

#include "../simplevaluelist.h"
#include "../simplevariable.h"

ProjectCompiler::ProjectCompiler(Project *project)
    : _project(project), _compilationFailed(false)
{
}

Program* ProjectCompiler::compile()
{
    return new Program(compileModel());
}

ProgramModel* ProjectCompiler::compileModel()
{
    ProgramModel* model = new ProgramModel();

    //compile each variable
    foreach (VarBlockRepr* varBlockRepr, _project->getVars()) {

        if(isListVar(varBlockRepr))
            model->getVarTable()->addList(new SimpleValueList(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
        else
            model->getVarTable()->addVariable(new SimpleVariable(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
    }

    //compile the screen
    compileScreen(model->getScreen());

    //check for no sprites
    if(_project->getSprites().size() == 0)
        setFailed(QObject::tr("No sprites are added"));

    //create the sprites
    QMap<SpriteRepr*, Sprite*> sprites;
    foreach (SpriteRepr* spriteRepr, _project->getSprites()) {
        sprites.insert(spriteRepr, createSprite(spriteRepr, model));
    }

    //create the UserStatements
    QMap<UserStatementRepr*, UserStatement*> userStatements;
    foreach(UserStatementRepr* userStatementRepr, _project->getUserStatements()) {
        userStatements.insert(userStatementRepr, createUserStatement(userStatementRepr, model));
    }

    //compile the sprites
    foreach (SpriteRepr* spriteRepr, _project->getSprites()) {
        QMap<SpriteRepr*, Sprite*>::iterator i = sprites.find(spriteRepr);
        compileSprite(spriteRepr, i.value(), sprites, userStatements, model);
    }

    //compile the userStatements
    foreach (UserStatementRepr* statementRepr, _project->getUserStatements()) {
        QMap<UserStatementRepr*, UserStatement*>::iterator i = userStatements.find(statementRepr);
        compileUserStatement(statementRepr, i.value(), userStatements, model);
    }

    return model;
}

void ProjectCompiler::compileScreen(Screen* screen)
{
    //create the screen
    ScreenRepr* screenRepr = _project->getScreen();

    //set the properties
    screen->setSize(screenRepr->getSize());
    if(screenRepr->useImage())
        screen->setBackground(new QPixmap(screenRepr->getBackgroundImage()));
    else
        screen->setColor(screenRepr->getBackgroundColor());
}

Sprite* ProjectCompiler::createSprite(SpriteRepr* spriteRepr, ProgramModel* model)
{
    //Create the sprite
    Sprite* sprite = model->createSprite(new QPixmap(*spriteRepr->getImages().first()));

    //add the different images
    for(int i = 1; i < spriteRepr->getImages().size(); i++)
        sprite->addImage(new QPixmap(*spriteRepr->getImages().at(i)));

    //Set the properties
    sprite->setSelectedImage(spriteRepr->getSelectedImageIndex());
    sprite->setPosition(spriteRepr->getPosition());
    sprite->setRotation(spriteRepr->getRotation());
    sprite->setSize(spriteRepr->getSize());

    return sprite;
}

UserStatement *ProjectCompiler::createUserStatement(UserStatementRepr *userStatementRepr, ProgramModel *model)
{
    if(userStatementRepr == NULL || model == NULL)
        return NULL;

    //create the UserStatement
    UserStatement* userStatement = new UserStatement(userStatementRepr->getParamTypes(), userStatementRepr->getParamNames());

    model->addUserStatement(userStatement);

    return userStatement;
}

void ProjectCompiler::compileSprite(SpriteRepr* spriteRepr, Sprite *sprite, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr *, UserStatement *> userStatements, ProgramModel* model)
{
    //Compile the blocks in the sprite
    foreach (BlockRepr* blockRepr, spriteRepr->getBlocks()) {
        //ignore non-event blocks
        if(blockRepr->getReturnType() == Block::EVENT) {
            sprite->addBlock(compileEventBlock(blockRepr, sprites, userStatements));
        }
    }

    //Add the variables to the sprite
    foreach (VarBlockRepr* varBlockRepr, spriteRepr->getVars()) {

        if(isListVar(varBlockRepr))
            sprite->getVarTable()->addList(new SimpleValueList(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
        else
            sprite->getVarTable()->addVariable(new SimpleVariable(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
    }
}

void ProjectCompiler::compileUserStatement(UserStatementRepr *userStatementRepr, UserStatement *userStatement, QMap<UserStatementRepr *, UserStatement *> userStatements, ProgramModel *model)
{
    //look for the first block
    BlockRepr* firstBlockRepr = NULL;
    foreach (BlockRepr* blockRepr, userStatementRepr->getBlocks()) {
        if(blockRepr->getReturnType() == Block::FUNCTION_START)
            firstBlockRepr = blockRepr;
    }

    if(firstBlockRepr == NULL) {
        setFailed(QObject::tr("UserStatement with no functionStartBlock exists"));
        return;
    }

    //compile the block following to the firstBlock
    StatementBlock* firstBlock = compileBody(firstBlockRepr->getNextStatement(), QMap<SpriteRepr*, Sprite*>(), userStatements);
    userStatement->setFirstBlock(firstBlock);

    //add the variables to the sprite
    foreach (VarBlockRepr* varBlockRepr, userStatementRepr->getVars()) {
        if(!userStatementRepr->isParamVar(varBlockRepr->getVarName())) {
            if(isListVar(varBlockRepr))
                userStatement->getVarTable()->addList(new SimpleValueList(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
            else {
                //if constant variable -> lock
                if(Block::isExpressionParam(varBlockRepr->getReturnType()))
                    userStatement->getVarTable()->addVariable(new SimpleVariable(varBlockRepr->getVarName(), getDataType(varBlockRepr), true));
                //if normal variable -> don't lock
                else
                    userStatement->getVarTable()->addVariable(new SimpleVariable(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
            }
        }
    }
}

EventBlock *ProjectCompiler::compileEventBlock(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr *, UserStatement *> userStatements)
{
    EventBlock* block = (EventBlock*)_project->getBlockLibrary()->getBlockInstance(blockRepr->getId());

    if(block == NULL) {
        setFailed(QObject::tr("The following block was not found: ") + blockRepr->getId());
        return NULL;
    }

    for(int i = 0; i < blockRepr->getNumParams(); i++) {
        block->addParameter(compileParam(blockRepr->getParam(i), sprites, userStatements), i);
    }

    block->setStatement(compileBody(blockRepr->getNextStatement(), sprites, userStatements));

    return block;
}

StatementBlock* ProjectCompiler::compileBody(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr *, UserStatement *> userStatements)
{
    StatementsBlock* statements = new StatementsBlock();

    if(blockRepr == NULL)
        return statements;

    do {
        statements->addStatement(compileStatement(blockRepr, sprites, userStatements));
        blockRepr = blockRepr->getNextStatement();
    } while(blockRepr != NULL);

    return statements;
}

StatementBlock* ProjectCompiler::compileStatement(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr *, UserStatement *> userStatements)
{
    if(blockRepr == NULL)
        return NULL;
    StatementBlock* statement = (StatementBlock*) _project->getBlockLibrary()->getBlockInstance(blockRepr->getId());

    //if statement was not found in the library
    if(statement == NULL) {
        //check if block is userStatement
        if(blockRepr->isUserStatementRepr()) {
            statement = compileUserStatementBlock(blockRepr, userStatements);
        }
        //if no user statement: no matching block was found, return NULL
        else {
            setFailed(QObject::tr("The following block was not found: ") + blockRepr->getId());
            return NULL;
        }
    }

    for(int i = 0; i < blockRepr->getNumParams(); i++) {
        statement->addParameter(compileParam(blockRepr->getParam(i), sprites, userStatements), i);
    }

    for(int i = 0; i < blockRepr->getNumBodies(); i++) {
        statement->addBody(compileBody(blockRepr->getBody(i), sprites, userStatements), i);
    }

    return statement;
}

Block* ProjectCompiler::compileParam(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr *, UserStatement *> userStatements)
{
    if(blockRepr == NULL) {
        setFailed(QObject::tr("Not all required parameters are filled"));
        return NULL;
    }

    if(Block::isExpressionParam(blockRepr->getReturnType()))
        return compileExpression(blockRepr, sprites, userStatements);

    if(Block::isVariableParam(blockRepr->getReturnType()))
        return compileVarBlock(blockRepr);

    if(Block::isListParam(blockRepr->getReturnType()))
        return compileListBlock(blockRepr);

    if(blockRepr->getReturnType() == Block::SPRITE)
        return compileSpriteBlock(blockRepr, sprites);

    return NULL;
}

ExpressionBlock* ProjectCompiler::compileExpression(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr *, UserStatement *> userStatements)
{
    if(blockRepr == NULL)
        return NULL;

    ExpressionBlock* expression = (ExpressionBlock*)_project->getBlockLibrary()->getBlockInstance(blockRepr->getId());

    if(expression == NULL) //if constant or variable
        return compileSpecialCaseExpression(blockRepr);

    for(int i = 0; i < blockRepr->getNumParams(); i++) {
        expression->addParameter(compileParam(blockRepr->getParam(i), sprites, userStatements), i);
    }

    return expression;
}

ExpressionBlock* ProjectCompiler::compileSpecialCaseExpression(BlockRepr* blockRepr)
{
    if(blockRepr == NULL)
        return NULL;

    //if constant:

    //true or false
    if(blockRepr->getId() == "Boolean_true")
        return new ConstantBlock(new BooleanValue(true));
    if(blockRepr->getId() == "Boolean_false")
        return new ConstantBlock(new BooleanValue(false));

    //number or string
    if(blockRepr->isConstantBlockRepr()) {
        if(blockRepr->getReturnType() == Block::STRING_EXPRESSION)
            return new ConstantBlock(new StringValue(((ConstantBlockRepr*)blockRepr)->getValue().toString()));
        if(blockRepr->getReturnType() == Block::NUMBER_EXPRESSION)
            return new ConstantBlock(new NumberValue(((ConstantBlockRepr*)blockRepr)->getValue().toDouble()));
    }

    //if variable:
    if(blockRepr->isVarBlockRepr())
        return compileVarBlock(blockRepr);

    //if everything fails:
    setFailed(QObject::tr("The following block was not found: ") + blockRepr->getId());
    return NULL;
}

VarBlock* ProjectCompiler::compileVarBlock(BlockRepr* blockRepr)
{
    Value::DataType dataType = Value::BOOLEAN;

    if(blockRepr->getReturnType() == Block::STRING_VAR || blockRepr->getReturnType() == Block::STRING_EXPRESSION)
        dataType = Value::STRING;

    else if(blockRepr->getReturnType() == Block::NUMBER_VAR || blockRepr->getReturnType() == Block::NUMBER_EXPRESSION)
        dataType = Value::NUMBER;

    return new VarBlock(((VarBlockRepr*)blockRepr)->getVarName(), dataType);
}


ListBlock* ProjectCompiler::compileListBlock(BlockRepr* blockRepr)
{
    Value::DataType dataType = Value::BOOLEAN;

    if(blockRepr->getReturnType() == Block::STRING_LIST)
        dataType = Value::STRING;

    else if(blockRepr->getReturnType() == Block::NUMBER_LIST)
        dataType = Value::NUMBER;

    return new ListBlock(((VarBlockRepr*)blockRepr)->getVarName(), dataType);
}

SpriteBlock* ProjectCompiler::compileSpriteBlock(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites)
{
    //pointer to the SpriteRepr represented by the param blockRepr
    SpriteRepr* spriteRepr = ((SpriteBlockRepr*)blockRepr)->getSpriteRepr();

    //Find the Sprite represented by spriteRepr
    QMap<SpriteRepr *, Sprite *>::iterator i = sprites.find(spriteRepr);
    //if not found
    if(i == sprites.end())
        return NULL;

    //create a SpriteBlock pointing to the Sprite
    return new SpriteBlock(i.value());
}

UserStatementBlock *ProjectCompiler::compileUserStatementBlock(BlockRepr *blockRepr, QMap<UserStatementRepr *, UserStatement *> userStatements)
{
    //pointer to the UserStatementRepr
    UserStatementRepr* usr = ((UserStatementBlockRepr*)blockRepr)->getUserStatementRepr();

    //find the corresponding UserStatement
    QMap<UserStatementRepr *, UserStatement *>::iterator i = userStatements.find(usr);
    //if not found
    if(i == userStatements.end())
        return NULL;

    //create the UserStatementBlock
    return new UserStatementBlock(i.value());
}

bool ProjectCompiler::isListVar(VarBlockRepr* varBlockRepr)
{
    Block::ParamType rtrn = varBlockRepr->getReturnType();

    return (rtrn == Block::BOOLEAN_LIST || rtrn == Block::NUMBER_LIST || rtrn == Block::STRING_LIST);
}

Value::DataType ProjectCompiler::getDataType(BlockRepr* blockRepr)
{
    Value::DataType dataType = Value::BOOLEAN;

    if(blockRepr->getReturnType() == Block::STRING_EXPRESSION || blockRepr->getReturnType() == Block::STRING_LIST || blockRepr->getReturnType() == Block::STRING_VAR)
        dataType = Value::STRING;

    else if(blockRepr->getReturnType() == Block::NUMBER_EXPRESSION || blockRepr->getReturnType() == Block::NUMBER_LIST || blockRepr->getReturnType() == Block::NUMBER_VAR)
        dataType = Value::NUMBER;

    return dataType;
}

void ProjectCompiler::setFailed(QString message)
{
    if(_compilationFailed)
        return;

    _compilationFailed = true;
    _compilationMessage = message;
}
