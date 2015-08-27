#ifndef PROGRAMMODEL_H
#define PROGRAMMODEL_H

#include "executionhandler.h"
#include "iohandler.h"
#include "screen.h"
#include "userstatement.h"

/**
 * @brief The ProgramModel class
 *
 * @author Brent Chesny
 */
class ProgramModel : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     */
    ProgramModel();

    /**
     * @brief Destructor method
     */
    ~ProgramModel();

    void startExecution() { _executionHandler->start(); }

    /**
     * @brief Sends a signal to all sprites
     * @param signal The signal to send
     */
    void sendSignal(const Signal &signal);

    /**
     * @brief Getter for the screen
     * @return The screen
     */
    Screen* getScreen() const { return _screen; }

    /**
     * @brief Adds a sprite to the programmodel and returns a pointer to this sprite
     */
    Sprite* createSprite(QPixmap* image);

    /**
     * @brief Returns a list of sprites
     * @return The list of sprites
     */
    QList<Sprite*> getSprites() const { return _sprites; }

    /**
     * @brief Returns the global var table
     * @return The global vartable
     */
    SimpleVarTable* getVarTable() const { return _globalVars; }

    /**
     * @brief Returns the executionHandler
     * @return Pointer to the executionHandler
     */
    ExecutionHandler* getExecutionHandler() const {return _executionHandler;}

    /**
     * @brief Returns the iohandler
     * @return Pointer to the iohandler
     */
    IOHandler* getIOHandler() const { return _ioHandler; }

    /**
     * @brief Adds a UserStatement to the program
     * @param userStatement The UserStatement to add
     */
    void addUserStatement(UserStatement* userStatement);

signals:
    void update();

private slots:
    void tickReceived();

private:

    ExecutionHandler* _executionHandler;

    IOHandler* _ioHandler;

    SimpleVarTable* _globalVars;

    Screen* _screen;

    QList<Sprite*> _sprites;

    QList<UserStatement*> _userStatements;

    bool _working;
};

#endif // PROGRAMMODEL_H
