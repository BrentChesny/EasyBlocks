#ifndef ARROWDOWNBLOCK_H
#define ARROWDOWNBLOCK_H


#include "../../eventblock.h"

/**
 * @brief The ArrowDownBlock class
 *
 * @author Brent Chesny
 */
class ArrowDownBlock : public EventBlock
{
public:
    /**
     * @brief Constructor method
     */
    ArrowDownBlock() {}

    /**
     * @brief Destructor
     */
    virtual ~ArrowDownBlock() {}

    /**
     * @brief Returns a unique id of the block
     * @return A unique id specific to the block
     */
    virtual QString getId() const {return QString("Event_ArrowDownEventBlock");}

    /**
     * @brief Returns a list of the paramtypes of the parameters
     * @return A QList<ParamType> containing the paramtype if each parameter
     */
    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    /**
     * @brief Returns the number of bodies of the block
     * @return The number of bodies of the block
     */
    virtual int getNumBodies() const {return 0;}

    /**
     * @brief Returns a description of the parameters
     * @return A description of the parameters
     */
    virtual QString getParamDescription() const {return QObject::tr("Arrow Down Pressed");}

    /**
     * @brief Returns a description of the bodies
     * @return A description of the bodies
     */
    virtual QString getBodiesDescription() const {return QString("");}

    /**
     * @brief Sends a signal to the Block. The block can react to this signal
     * @param signal The signal to send to the block
     */
    virtual void sendSignal(const Signal& signal, Sprite* sprite);

    /**
     * @brief Adds a parameterBlock to this Block
     * @param parameter The block to add
     * @param index The index of the parameter
     * @return True if adding succeeded , false if not
     */
    virtual bool addParameter(Block* parameter, int index) {return false;}

    /**
     * @brief Adds a body to this block
     * @param body The block to add
     * @param index The index of the body
     * @return True if adding succeeded, false if not
     */
    virtual bool addBody(StatementBlock* body, int index) {return false;}

    /**
     * @brief Creates a new instance of the block and returns it
     * @return A new instance of the block
     */
    virtual Block* newInstance() const {return new ArrowDownBlock();}
};

#endif // ARROWDOWNBLOCK_H
