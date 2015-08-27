#include "arrowrightblock.h"

#include "../../executionhandler.h"
#include "../../statementblock.h"
#include "../../programmodel.h"


void ArrowRightBlock::sendSignal(const Signal& signal, Sprite* sprite)
{
    //check pointer and type of signal
    if(sprite == NULL || signal.getType() != Signal::ARROW_RIGHT)
        return;

    //run statements
    sprite->getProgramModel()->getExecutionHandler()->addExecutionThread(getStatement(), sprite->getVarTable(), sprite);
}
