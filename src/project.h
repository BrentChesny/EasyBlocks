#ifndef PROJECT_H
#define PROJECT_H

#include <QList>

#include "spriterepr.h"
#include "screenrepr.h"
#include "blocklibrary.h"
#include "blockreprlibrary.h"
#include "blockrepr/varblockrepr.h"
#include "program.h"
#include "userstatementrepr.h"
#include "blockrepr/userstatementblockrepr.h"

/**
 * @brief The Project class
 *
 * @author Brent Chesny
 */
class Project : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constrcutor method
     */
    Project();

    /**
     * @brief Destructor method
     */
    ~Project();

    /**
     * @brief Returns a pointer to the screen representation object
     * @return A pointer to the screen representation object
     */
    ScreenRepr* getScreen() const { return _screen; }

    /**
     * @brief Setter for the screen of the project
     * @param screen The screen to set
     */
    void setScreen(ScreenRepr* screen);

    /**
     * @brief Returns a pointer to the blockrepresentation library
     * @return A pointer to the blockrepresentation library
     */
    BlockReprLibrary* getBlockReprLibrary() const { return _blockReprLibrary; }

    /**
     * @brief Returns a pointer to the block library
     * @return A pointer to the block library
     */
    BlockLibrary* getBlockLibrary() const { return _blockLibrary; }

    /**
     * @brief Returns a list of pointer to all sprites
     * @return A list of pointers to all sprites
     */
    QList<SpriteRepr*> getSprites() const { return _sprites; }

    /**
     * @brief Setter for the index of the currently selected sprite
     * @param index The index of the selected sprite
     */
    void setCurrentSpriteIndex(int index) { _currentSpriteIndex = index; _currentFuncIndex = -1; sendUpdate(); }


    void setCurrentFuncIndex(int index) { _currentFuncIndex = index; _currentSpriteIndex = -1; sendUpdate(); }
    int getCurrentFuncIndex() const { return _currentFuncIndex; }
    UserStatementRepr *getCurrentFunc() const;

    /**
     * @brief Sets the current sprite index based on a given sprite
     * @param sprite The sprite that should be selected
     */
    void setCurrentSprite(SpriteRepr* sprite) { _currentSpriteIndex = _sprites.indexOf(sprite); sendUpdate(); }

    /**
     * @brief Returns a pointer to the currently selected sprite
     * @return A pointer to the currently selected sprite
     */
    SpriteRepr* getCurrentSprite() const;

    /**
     * @brief Returns the index of the given sprite
     * @param sprite The sprite to return the index from
     * @return The index of the sprite, -1 if the sprite doesn't exist
     */
    int getIndexOfSprite(SpriteRepr* sprite);

    /**
     * @brief Returns the index of the current sprite
     * @return The index of the current sprite
     */
    int getCurrentSpriteIndex() const { return _currentSpriteIndex; }

    /**
     * @brief Adds a new sprite to the project
     * @param image The image of the sprite
     * @param name The name of the sprite
     */
    void addSprite(QPixmap* image, QString name);

    /**
     * @brief Adds a new sprite
     * @param sprite The sprite to add
     */
    void addSprite(SpriteRepr* sprite);

    /**
     * @brief Removes the sprite with the given index
     * @param index The index of the sprite
     */
    void removeSprite(int index);

    /**
     * @brief Moves the current sprite up in the list
     */
    void moveSpriteUp();

    /**
     * @brief Moves the current sprite down in the list
     */
    void moveSpriteDown();

    /**
     * @brief Creates a runnable program
     * @return A runnable program
     */
    Program* createRunnableProgram();

    /**
     * @brief Adds a variable to the project
     * @param The variable to add
     */
    void addVariable(VarBlockRepr* var);

    /**
     * @brief Removes a variable from the project
     * @param var The variable to remove
     */
    void removeVariable(VarBlockRepr* var);

    /**
     * @brief Returns if there already is a var with the given name
     * @param name The name of the var
     * @return True if the var with the given name already exists
     */
    bool hasVariableWithName(QString name);

    /**
     * @brief Returns the global variables in the project
     * @return A list of the global vars in the project
     */
    QList<VarBlockRepr*> getVars() const { return _vars; }

    /**
     * @brief Returns the path of this project
     * @return The path of the project
     */
    QString getPath() const { return _path; }

    /**
     * @brief Sets the path of the project
     * @param path The path of the project
     */
    void setPath(QString path) { _path = path; }

    /**
     * @brief Duplicates the current sprite
     */
    void duplicateCurrentSprite();

    /**
     * @brief Runs an existance check over the sprites to remove special blocks referencing to no longer existing variables and sprites
     */
    void checkExistance();

    /**
     * @brief Adds a UserStatement to the Project
     * @param userStatement the UserStatementRepr to add
     */
    void addUserStatement(UserStatementRepr* userStatement);

    /**
     * @brief Removes a UserStatement from the Project
     * @param userStatement The UserStatementRepr to remove
     */
    void removeUserStatement(UserStatementRepr* userStatement);

    /**
     * @brief Returns the list of UserStatements in this Project
     * @return A list containing all the UserStatementRepr in this Project
     */
    QList<UserStatementRepr*> getUserStatements() const {return _userStatements;}

    /**
     * @brief Returns the list of UserStatementBlockReprs in this Project
     * @return The list of UserStatementBlockReprs in this project
     */
    QList<UserStatementBlockRepr*> getUserStatementBlockReprs();

    int getIndexOfUserStatement(UserStatementRepr* us);

    /**
     * @brief Reloads the BlockReprLibrary from the BlockLibrary
     */
    void reloadBlockReprLibrary();

signals:
    void updated();

public slots:
    void sendUpdate();

private:
    QString _path;

    ScreenRepr* _screen;

    QList<VarBlockRepr*> _vars;

    QList<SpriteRepr*> _sprites;

    QList<UserStatementRepr*> _userStatements;

    QList<UserStatementBlockRepr*> _userStatementBlockReprs;

    BlockLibrary* _blockLibrary;

    BlockReprLibrary* _blockReprLibrary;

    int _currentSpriteIndex;

    int _currentFuncIndex;
};

#endif // PROJECT_H
