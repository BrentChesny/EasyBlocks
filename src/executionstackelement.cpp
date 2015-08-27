#include "executionstackelement.h"

ExecutionStackElement::~ExecutionStackElement()
{
    if(_message != NULL)
        delete _message;
}

void ExecutionStackElement::setMessage(Message* message) {
    if(_message != NULL)
        delete _message;

    _message = message;
}

ExecutionStackElement* ExecutionStackElement::getCopy() const {
    ExecutionStackElement* ese = new ExecutionStackElement();

    ese->setMessage(NULL);
    ese->setSprite(_sprite);
    ese->setBlock(_block);
    ese->setVarTable(_varTable);

    return ese;
}
