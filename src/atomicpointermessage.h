#ifndef ATOMICPOINTERMESSAGE_H
#define ATOMICPOINTERMESSAGE_H

#include "message.h"

#include <QAtomicPointer>
#include <QString>

/**
 * @brief The atomicPointerMessage class
 *
 * @author Brecht Vandevoort
 */
class AtomicPointerMessage : public Message
{
public:
    /**
     * @brief Constructor
     * @param value The value
     * @param atomicPtr The QAtomicPointer
     */
    AtomicPointerMessage(int value = 0, QAtomicPointer<QString>* atomicPtr = NULL)
        : _value(value), _atomicPtr(atomicPtr) {}

    /**
     * @brief Destructor
     */
    ~AtomicPointerMessage();

    /**
     * @brief Sets the value
     * @param value The value to set
     */
    void setValue(int value) {_value = value;}

    /**
     * @brief Returns the current value
     * @return The current value
     */
    int getValue() const {return _value;}

    /**
     * @brief Sets the atomic pointer
     * @param atomicPtr The atomic pointer to set
     */
    void setAtomicPointer(QAtomicPointer<QString>* atomicPtr) {_atomicPtr = atomicPtr;}

    /**
     * @brief Returns the atomic pointer
     * @return The atomic pointer
     */
    QAtomicPointer<QString>* getAtomicPointer() const {return _atomicPtr;}

private:
    int _value;
    QAtomicPointer<QString>* _atomicPtr;
};

#endif // ATOMICPOINTERMESSAGE_H
