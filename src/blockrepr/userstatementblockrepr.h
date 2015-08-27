#ifndef USERSTATEMENTBLOCKREPR_H
#define USERSTATEMENTBLOCKREPR_H

#include "../blockrepr.h"

#include "../userstatementrepr.h"

/**
 * @brief The UserStatementBlockRepr class
 *
 * @author Brecht Vandevoort
 */
class UserStatementBlockRepr : public BlockRepr
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param userStatement The UserStatementRepr this block represents
     * @param locked if true, no changes to the block are allowed
     */
    UserStatementBlockRepr(UserStatementRepr* userStatement, bool locked = false);

    /**
     * @brief Copy constructor
     * @param userStatementBlockRepr The UserStatementBlockRepr to copy
     */
    UserStatementBlockRepr(const UserStatementBlockRepr& userStatementBlockRepr);

    /**
     * @brief Creates a copy of this block
     * @return Pointer to the copy of this block
     */
    virtual BlockRepr* copy();

    /**
     * @brief Returns the UserStatementRepr this block represents
     * @return Pointer to a UserStatementRepr
     */
    UserStatementRepr* getUserStatementRepr() const {return _userStatement;}

    /**
     * @brief virtual function overloaded from BlockRepr to indicate that this blockRepr is an UserStatementBlockRepr
     * @return Always true
     */
    bool isUserStatementRepr() const {return true;}

private:
    UserStatementRepr* _userStatement;
};

#endif // USERSTATEMENTBLOCKREPR_H
