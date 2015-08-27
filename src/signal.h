#ifndef SIGNAL_H
#define SIGNAL_H

#include <QString>

/**
 * @brief The Signal class
 *
 * @author Brecht Vandevoort
 */
class Signal
{
public:

    /**
     * @brief The SignalType enum
     */
    enum SignalType {START, BUTTONCLICKED, MOUSECLICKED, MESSAGE,
                     ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT,
                     SPACE, ENTER};

    /**
     * @brief Constructor
     * @param signalType The type of the signal
     */
    Signal(SignalType signalType) : _signalType(signalType), _message(QString("")) {}

    /**
     * @brief Constructor
     * @param signalType The type of the signal
     * @param message The message of the signal
     */
    Signal(SignalType signalType, const QString& message) : _signalType(signalType), _message(message) {}

    /**
     * @brief Returns the message of the signal
     * @return The message of the signal
     */
    QString getMessage() const {return _message;}

    /**
     * @brief Returns the type of the signal
     * @return The type of the signal
     */
    SignalType getType() const {return _signalType;}

private:
    SignalType _signalType;
    QString _message;
};

#endif // SIGNAL_H
