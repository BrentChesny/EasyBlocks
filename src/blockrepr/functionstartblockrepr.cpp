#include "functionstartblockrepr.h"

FunctionStartBlockRepr::FunctionStartBlockRepr() : BlockRepr(Block::FUNCTION_START)
{
    setParamLabels("Function Start");
}

FunctionStartBlockRepr::FunctionStartBlockRepr(const FunctionStartBlockRepr &functionStartBlockRepr)
 : BlockRepr(Block::FUNCTION_START)
{
    setParamLabels("Function Start");
}
