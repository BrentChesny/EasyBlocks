#ifndef USERSTATEMENTREPR_H
#define USERSTATEMENTREPR_H

#include <QObject>
#include <QList>
#include <QStringList>

#include "blockreprholder.h"
#include "blockrepr/varblockrepr.h"

/**
 * @brief The UserStatementRepr class
 *
 * @author Brecht Vandevoort
 */
class UserStatementRepr : public BlockReprHolder
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    UserStatementRepr(QString paramDesciption, QList<Block::ParamType> paramTypes, QStringList paramNames);

    /**
     * @brief Destructor
     */
    ~UserStatementRepr();

    /**
     * @brief Adds a variable
     * @param var The var to add
     */
    void addVariable(VarBlockRepr* var);

    /**
     * @brief Removes a variable
     * @param var The variable to remove
     */
    void removeVariable(VarBlockRepr* var);

    /**
     * @brief Returns the list of variables
     * @return The list of variables
     */
    QList<VarBlockRepr*> getVars() const {return _vars;}

    /**
     * @brief Returns the ParamTypes of the params
     * @return List of the paramTypes
     */
    QList<Block::ParamType> getParamTypes() const {return _paramTypes;}

    /**
     * @brief Returns the description of the params
     * @return The parameter description
     */
    QString getParamDescription() const {return _paramDescription;}

    /**
     * @brief Returns the parameter names
     * @return List containing the parameter names
     */
    QStringList getParamNames() const {return _paramNames;}

    bool isParamVar(QString varName) const {return _paramNames.contains(varName);}

    void addStartBlock();

signals:

private:
    QList<VarBlockRepr*> _vars;

    //function info
    QList<Block::ParamType> _paramTypes;
    QString _paramDescription;
    QStringList _paramNames;
};

#endif // USERSTATEMENTREPR_H
