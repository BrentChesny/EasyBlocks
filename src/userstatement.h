#ifndef USERSTATEMENT_H
#define USERSTATEMENT_H

#include "simplevartable.h"
#include "statementblock.h"

#include <QStringList>

/**
 * @brief The UserStatement class, representing a user-defined StatementBlock
 *
 * @author Brecht Vandevoort
 */
class UserStatement
{
public:
    /**
     * @brief Constructor
     */
    UserStatement(const QList<Block::ParamType> &paramTypes, const QStringList& paramNames);

    /**
     * @brief Destructor
     */
    ~UserStatement();

    /**
     * @brief Returns the VarTable
     * @return Pointer to the VarTable
     */
    VarTable* getVarTable() const {return _vars;}

    /**
     * @brief Sets the first block to be executed
     * @param firstBlock The first block to be executed
     */
    void setFirstBlock(StatementBlock* firstBlock);

    /**
     * @brief Getter for the first block to be executed
     * @return Pointer to the first block to be executed
     */
    StatementBlock* getFirstBlock() const {return _firstBlock;}

    /**
     * @brief Getter for the paramTypes
     * @return List containing the paramtype of each parameter
     */
    QList<Block::ParamType> getParamTypes() const {return _paramTypes;}

    /**
     * @brief Returns the number of parameters
     * @return The number of parameters
     */
    int getNumParams() const {return _paramTypes.size();}

    /**
     * @brief Returns the description of the parameters
     * @return Description of the parameters
     */
    QString getParamDescription() const {return _paramDescription;}

    /**
     * @brief Sets the paramDescription
     * @param paramDescription Description of the parameters
     */
    void setParamDescription(const QString &paramDescription);

    /**
     * @brief Returns the names of the different parameters
     * @return QStringList containing the names of the different parameters
     */
    QStringList getParamNames() const {return _paramNames;}

private:
    StatementBlock* _firstBlock;
    SimpleVarTable* _vars;
    QList<Block::ParamType> _paramTypes;
    QString _paramDescription;
    QStringList _paramNames;
};

#endif // USERSTATEMENT_H
