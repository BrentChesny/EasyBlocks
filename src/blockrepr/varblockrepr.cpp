#include "varblockrepr.h"
#include "../project.h"

VarBlockRepr::VarBlockRepr(Block::ParamType returnType, QString varName, Project *project, bool locked)
    : BlockRepr(returnType, varName, locked), _varName(varName), _project(project)
{

}

VarBlockRepr::VarBlockRepr(const VarBlockRepr &block) : BlockRepr(block.getReturnType(), block.getVarName(), block.isLocked()), _varName(block._varName), _project(block.getProject())
{
}

BlockRepr* VarBlockRepr::copy()
{
    return new VarBlockRepr(*this);
}

void VarBlockRepr::checkExistance(Project* project)
{
    if (!project->hasVariableWithName(_varName))
        removeFromParent();
}

void VarBlockRepr::deleteVariable() {
    if(_project->getCurrentSpriteIndex() >= 0)
        _project->removeVariable(this);
    else if(_project->getCurrentFuncIndex() >= 0)
        _project->getCurrentFunc()->removeVariable(this);
    delete this;
}
