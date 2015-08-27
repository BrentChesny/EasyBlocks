#ifndef VARTABLE_H
#define VARTABLE_H

#include "variable.h"
#include "valuelist.h"

/**
 * @brief The VarTable class
 *
 * @author Brent Chesny
 */
class VarTable
{
public:
    /**
     * @brief Constructor method
     */
    VarTable();

    /**
     * @brief Destructor method
     */
    virtual ~VarTable();

    /**
     * @brief Returns the value of the variable with a given name
     * @param name The name of the variable
     * @return The value of the variable with a given name
     */
    virtual Value* getValue(QString name) const = 0;

    /**
     * @brief Sets a value for a variable with a given name
     * @param name The name of the variable to set
     * @param value The value to set
     * @return Returns true when the value has been set, false if the variable didn't exist
     */
    virtual bool setValue(QString name, Value* value) = 0;

    /**
     * @brief Adds a Variable to the vartable
     * @param var The variable to add to the table
     */
    virtual void addVariable(Variable* var) = 0;

    /**
     * @brief Returns a Variable with the given name
     * @param name Name of the variable to return
     * @return  The Variable with the given name
     */
    virtual Variable* getVariable(QString name) const = 0;

    /**
     * @brief Returns a valuelist with a given name
     * @param name The name of the list to return
     * @return The list with a given name
     */
    virtual ValueList* getList(QString name) const = 0;

    /**
     * @brief Adds a list to the table
     * @param list The list to add to the table
     */
    virtual void addList(ValueList* list) = 0;

    /**
     * @brief Returns a copy of the vartable
     * @return A copy of the vartable.
     */
    virtual VarTable* copy() = 0;
};

#endif // VARTABLE_H
