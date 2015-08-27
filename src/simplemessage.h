#ifndef SIMPLEMESSAGE_H
#define SIMPLEMESSAGE_H

#include "message.h"

#include <QString>

/**
 * @brief The SimpleMessage class
 *
 * @author Brecht Vandevoort
 */
class SimpleMessage : public Message
{
public:
    /**
     * @brief Constructor
     * @param message The message of the SimpleMessage
     */
    SimpleMessage(const QString& message) : _message(message) {}

    /**
     * @brief Destructor
     */
    SimpleMessage() {}

    /**
     * @brief Returns the message of the SimpleMessage
     * @return The message of the SimpleMessage
     */
    QString getMessage() const {return _message;}

private:
    QString _message;
};

#endif // SIMPLEMESSAGE_H
