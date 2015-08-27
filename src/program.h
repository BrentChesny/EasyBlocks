#ifndef PROGRAM_H
#define PROGRAM_H

#include "programmodel.h"
#include "programwindow.h"

/**
 * @brief The Program class
 *
 * @author Brent Chesny
 */
class Program : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     */
    Program(ProgramModel* model);

    /**
     * @brief Destructor method
     */
    ~Program();

    /**
     * @brief Opens the program window and starts te execution.
     */
    void start();

    /**
     * @brief Stops the running program.
     */
    void stop();

    /**
     * @brief Pauses the running program.
     * @return Returns true if the program is running after the pause
     */
    bool pause();


signals:
    void stopped();

public slots:
    void emitStopped();

private:
    ProgramModel* _model;

    ProgramWindow* _window;
};

#endif // PROGRAM_H
