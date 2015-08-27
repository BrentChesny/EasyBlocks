#include "userstatementblock.h"

#include "executionthread.h"
#include "aliasvaluelist.h"
#include "simplevariable.h"
#include "aliasvariable.h"
#include "varblock.h"
#include "listblock.h"

#include <QDebug>

UserStatementBlock::UserStatementBlock(UserStatement *userStatement)
    : _userStatement(userStatement), _params(NULL)
{
    if(_userStatement != NULL) {
        _paramsSize = _userStatement->getNumParams();
        _params = new Block*[_paramsSize];
        for(int i = 0; i < _paramsSize; i++)
            _params[i] = NULL;
    }
}

UserStatementBlock::~UserStatementBlock()
{
    if(_params != NULL) {
        for(int i = 0; i < _paramsSize; i++)
            if(_params[i] != NULL)
                delete _params[i];
        delete [] _params;
    }
}

QList<Block::ParamType> UserStatementBlock::getParamTypes() const
{
    if(_userStatement != NULL)
        return _userStatement->getParamTypes();
    else
        return QList<Block::ParamType>();
}

QString UserStatementBlock::getParamDescription() const
{
    if(_userStatement != NULL)
        return _userStatement->getParamDescription();
    else
        return QString();
}

void UserStatementBlock::executeNextStep(ExecutionThread &executionThread) const
{
    //check if block is valid for execution
    for(int i = 0; i < _paramsSize; i++) {
        if(_params[i] == NULL) {
            executionThread.endExecution(NULL);
            return;
        }
    }

    //get message
    ValueListMessage* m = (ValueListMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new ValueListMessage(0);
        executionThread.setMessage(m);
    }

    //evaluate parameters
    if(m->getNumber() < _paramsSize)
    {
        //store previous parameter value
        if(m->getNumber() > 0)
            storeParam(m->getNumber()-1, executionThread, m);
        //evalute next parameter
        evaluateParam(m->getNumber(), executionThread, m);
        //change number in message
        m->setNumber(m->getNumber()+1);
        return;
    }

    //run function
    if(m->getNumber() == _paramsSize) {
        //store previous parameter value
        if(m->getNumber() > 0)
            storeParam(m->getNumber()-1, executionThread, m);
        //run function
        runUserStatement(executionThread, m);
        m->setNumber(m->getNumber()+1);
        return;
    }

    //function ended -> clear function
    if(m->getNumber() == _paramsSize+1) {
        delete executionThread.getVarTable();
        executionThread.endExecution(NULL);
        return;
    }

    executionThread.endExecution(NULL);
}

bool UserStatementBlock::addParameter(Block *parameter, int index)
{
    if(_userStatement == NULL || index < 0 || index >= _paramsSize || parameter == NULL)
        return false;

    if(Block::isValidParam(parameter->getReturnType(), _userStatement->getParamTypes().at(index))) {
        if(_params[index] != NULL)
            delete _params[index];
        _params[index] = parameter;
        return true;
    }

    return false;
}

void UserStatementBlock::evaluateParam(int index, ExecutionThread &executionThread, ValueListMessage *message) const
{
    if(index < 0 || index >= _paramsSize)
        return;

    Block::ParamType paramType  = _userStatement->getParamTypes().at(index);
    //if an expression -> evaluate value
    if(paramType == Block::BOOLEAN_EXPRESSION || paramType == Block::NUMBER_EXPRESSION || paramType == Block::STRING_EXPRESSION) {
        executionThread.setNextBlock(_params[index]);
    }
}

void UserStatementBlock::storeParam(int index, ExecutionThread &executionThread, ValueListMessage *message) const
{
    if(index < 0 || index >= _paramsSize)
        return;

    Block::ParamType paramType  = _userStatement->getParamTypes().at(index);
    //if an expression -> store value
    if(paramType == Block::BOOLEAN_EXPRESSION || paramType == Block::NUMBER_EXPRESSION || paramType == Block::STRING_EXPRESSION) {
        Value* value = executionThread.getReturnValue();
        //check if value of previous parameter is valid
        if(value == NULL || value->getDataType() != toDataType(paramType)) {
            executionThread.endExecution(NULL);
            return;
        }
        //store value in message
        message->setValAt(index, value->copy());
    }
}

void UserStatementBlock::runUserStatement(ExecutionThread &executionThread, ValueListMessage *message) const
{
    //create VarTable
    VarTable* vt = _userStatement->getVarTable()->copy();

    //add parameters to VarTable
    for(int i = 0; i < _paramsSize; i++) {
        //expression
        if(isExpressionParam(_userStatement->getParamTypes().at(i))) {
            SimpleVariable* exprVar = new SimpleVariable(_userStatement->getParamNames().at(i), toDataType(_userStatement->getParamTypes().at(i)), true);
            exprVar->forceValue(message->getValAt(i)->copy());
            vt->addVariable(exprVar);
        }
        //variable
        else if(isVariableParam(_userStatement->getParamTypes().at(i))) {
            //look for variable in varTable
            QString varName = ((VarBlock*)_params[i])->getVarName();
            Variable* var = executionThread.getVarTable()->getVariable(varName);
            if(var != NULL) {
                vt->addVariable(new AliasVariable(_userStatement->getParamNames().at(i), var));
            }
        }
        //list
        else if(isListParam(_userStatement->getParamTypes().at(i))) {
            QString listName = ((ListBlock*)_params[i])->getListName();
            ValueList* list = executionThread.getVarTable()->getList(listName);
            if(list != NULL) {
                vt->addList(new AliasValueList(_userStatement->getParamNames().at(i), list));
            }
        }
    }

    //change varTable on top of executionstack in the executionthread
    executionThread.setVarTable(vt);

    //set first block to run
    executionThread.setNextBlock(_userStatement->getFirstBlock());
}

Value::DataType UserStatementBlock::toDataType(Block::ParamType paramType) const
{
    if(paramType == Block::BOOLEAN_EXPRESSION || paramType == Block::BOOLEAN_LIST || paramType == Block::BOOLEAN_VAR)
        return Value::BOOLEAN;

    if(paramType == Block::NUMBER_EXPRESSION || paramType == Block::NUMBER_LIST || paramType == Block::NUMBER_VAR)
        return Value::NUMBER;

    if(paramType == Block::STRING_EXPRESSION || paramType == Block::STRING_LIST || paramType == Block::STRING_VAR)
        return Value::STRING;

    //default
    return Value::BOOLEAN;
}
