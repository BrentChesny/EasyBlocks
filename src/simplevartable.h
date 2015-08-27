#ifndef SIMPLEVARTABLE_H
#define SIMPLEVARTABLE_H

#include "vartable.h"


/**
 * @brief The SimpleVarTable class
 *
 * @author Brent Chesny
 */
class SimpleVarTable : public VarTable
{
public:
    /**
     * @brief Constructor method
     */
    SimpleVarTable();

    /**
     * @brief Destructor method
     */
    virtual ~SimpleVarTable();

    /**
     * @brief Returns the value of the variable with a given name
     * @param name The name of the variable
     * @return The value of the variable with a given name
     */
    virtual Value* getValue(QString name) const;

    /**
     * @brief Sets a value for a variable with a given name
     * @param name The name of the variable to set
     * @param value The value to set
     * @return Returns true when the value has been set, false if the variable didn't exist
     */
    virtual bool setValue(QString name, Value* value);

    /**
     * @brief Adds a Variable to the vartable
     * @param variable The variable to add to the table
     */
    virtual void addVariable(Variable* variable);

    /**
     * @brief Returns a Variable with the given name
     * @param name Name of the variable to return
     * @return  The Variable with the given name
     */
    virtual Variable* getVariable(QString name) const;

    /**
     * @brief Returns a valuelist with a given name
     * @param name The name of the list to return
     * @return The list with a given name
     */
    virtual ValueList* getList(QString name) const;

    /**
     * @brief Adds a list to the table
     * @param list The list to add to the table
     */
    virtual void addList(ValueList* list);

    /**
     * @brief Returns a copy of the vartable
     * @return A copy of the vartable
     */
    VarTable *copy();

    /**
     * @brief Returns the list of variables
     * @return The list of variables
     */
    QList<Variable*> getVariables() const { return _variables; }

    /**
     * @brief Returns the list of lists
     * @return The list of lists
     */
    QList<ValueList*> getLists() const { return _lists; }

private:
    QList<Variable*> _variables;

    QList<ValueList*> _lists;
};

#endif // SIMPLEVARTABLE_H
