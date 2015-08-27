#include "atomicpointermessage.h"


AtomicPointerMessage::~AtomicPointerMessage()
{
    if(_atomicPtr != NULL)
        delete _atomicPtr;
}
