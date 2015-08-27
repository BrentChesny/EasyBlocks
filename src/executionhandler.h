#ifndef EXECUTIONHANDLER_H
#define EXECUTIONHANDLER_H

#include "executionthread.h"
#include "iohandler.h"

#include <QObject>
#include <QThread>
#include <QList>
#include <QTimer>
#include <QDateTime>

/**
 * @brief The ExecutionHandler class
 *
 * @author Brecht Vandevoort
 */
class ExecutionHandler : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Time between two execution steps, in milliseconds
     */
    static const int EXECUTION_TICK_INTERVAL = 5;

    /**
     * @brief Time between two drawing steps, in milliseconds
     */
    static const int DRAW_TICK_INTERVAL = 5;

    /**
     * @brief Constructor
     */
    ExecutionHandler(IOHandler* ioHandler);

    /**
     * @brief Destructor
     */
    ~ExecutionHandler();

    /**
     * @brief Starts the executionHandler to execute blocks
     */
    void start();

    /**
     * @brief Stops the ExecutionHandler executing blocks
     */
    void stop();

    /**
     * @brief Returns the number of ExecutionThreads the ExecutionHandler currently contains
     * @return The number of ExecutionThreads
     */
    int getNumThreads() const;

    /**
     * @brief Creates a new ExecutionThread to execute the given block
     * @param block The block to execute in the new ExecutionThread
     * @param varTable The varTable to use
     * @param sprite The sprite to use
     */
    void addExecutionThread(Block* block, VarTable* varTable, Sprite* sprite);

    /**
     * @brief Returns if the handler is running
     * @return True if running
     */
    bool isRunning() const { return _running; }

public slots:
    /**
     * @brief Slot for doing a tick. The executionHandler will execute a single step in an ExecutionThread
     */
    void executionTick();

signals:
    /**
     * @brief This Signal is sent every time the ExecutionHandler does an executiontick
     */
    void executionTicked();

    /**
     * @brief This Signal is sent every time the ExecutionHandler does a drawingtick
     */
    void drawingTicked();


private:
    QList<ExecutionThread*> _threads;
    IOHandler* _ioHandler;
    QTimer* _qtimer;
    bool _running;
    bool _working;

    QDateTime _prevExecutionTime;
    QDateTime _prevDrawTime;

    /**
     * @brief executeThread Executes a single step in every ExecutionThread.
     */
    void executeThreads();
};

#endif // EXECUTIONHANDLER_H
