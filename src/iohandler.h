#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QObject>
#include <QQueue>
#include <QPair>
#include <QAtomicPointer>

/**
 * @brief The IOHandler class
 *
 * @author Brecht Vandevoort
 */
class IOHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     */
    IOHandler() {}

    /**
     * @brief Destructor
     */
    ~IOHandler() {}

    /**
     * @brief Asks the user for input
     * @param question The question to ask
     * @param input Pointer to where the answer needs te be stored, if NULL, the request will be ignored
     */
    void getInput(const QString& question, QAtomicPointer<QString>* input);

    /**
     * @brief Writes output.
     * @param output The output to write
     */
    void writeOutput(const QString& output) {emit outputReceived(output);}

    /**
     * @brief Returns the first input question
     * @return The first input question, or a nullstring if the queue is empty
     */
    QString getFirstInputQuestion() const;

signals:
    /**
     * @brief This signal is emitted every time this IOHandler receives output
     * @param output The output received
     */
    void outputReceived(const QString& output);

    /**
     * @brief This signal is emitted every time this IOHandler receives an input request
     */
    void inputRequestReceived();

public slots:
    /**
     * @brief This slot is called to transfer input into the handler
     * @param input The input to handle
     */
    void sendInput(const QString& input);

private:
    //QAtomicPointer is used to allow atomic reading and writing, because this pointer is used in multiple threads
    QQueue<QPair<QString, QAtomicPointer<QString>*> > _inputQueue;
};

#endif // IOHANDLER_H
