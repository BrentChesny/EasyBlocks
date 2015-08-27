#include "iohandler.h"

void IOHandler::getInput(const QString& question, QAtomicPointer<QString> *input)
{
    //ignore if no input given
    if(input == NULL)
        return;

    //add question to queue
    _inputQueue.append(QPair<QString, QAtomicPointer<QString>*>(question, input));

    emit inputRequestReceived();
}

QString IOHandler::getFirstInputQuestion() const
{
    if(_inputQueue.isEmpty())
        return QString();

    return _inputQueue.first().first;
}

void IOHandler::sendInput(const QString& input)
{
    if(_inputQueue.isEmpty())
        return;

    QAtomicPointer<QString>* inputPtr = _inputQueue.dequeue().second;

    inputPtr->store(new QString(input));
}
