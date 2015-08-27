#ifndef VARBLOCKREPR_H
#define VARBLOCKREPR_H

#include "../blockrepr.h"

/**
 * @brief The VarBlockRepr class
 *
 * @author Brent Chesny
 */
class VarBlockRepr : public BlockRepr
{
    Q_OBJECT
public:
    VarBlockRepr(Block::ParamType returnType, QString varName, Project* project, bool locked = false);

    VarBlockRepr(const VarBlockRepr& block);

    QString getVarName() const {return _varName;}

    Project* getProject() const { return _project; }

    virtual BlockRepr* copy();

    virtual bool isVarBlockRepr() const { return true; }
    virtual void checkExistance(Project* project);


public slots:
    void deleteVariable();

private:
    QString _varName;
    Project* _project;
};

#endif // VARBLOCKREPR_H
