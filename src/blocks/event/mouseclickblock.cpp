#include "mouseclickblock.h"

#include "../../executionhandler.h"
#include "../../statementblock.h"
#include "../../programmodel.h"


void MouseClickBlock::sendSignal(const Signal& signal, Sprite* sprite)
{
    //check pointer and type of signal
    if(sprite == NULL || signal.getType() != Signal::MOUSECLICKED)
        return;

    //run statements
    sprite->getProgramModel()->getExecutionHandler()->addExecutionThread(getStatement(), sprite->getVarTable(), sprite);
}
