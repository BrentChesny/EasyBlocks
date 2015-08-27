#ifndef NUMBERVAL_H
#define NUMBERVAL_H

#include "value.h"

#include <QString>
#include <QDebug>

/**
 * @brief The NumberValue class
 *
 * @author Brent Chesny
 */
class NumberValue : public Value
{
public:
    /**
     * @brief Constructor method
     */
    NumberValue(double value) : _value(value) {}

    virtual ~NumberValue() {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    DataType getDataType() const { return NUMBER; }

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    double toDouble() const { return _value; }

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    QString toString() const { return QString::number(_value); }

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    bool toBool() const { return (_value > 0.99999 && _value < 1.00001); }

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    Value* copy() const;

private:
    double _value;
};

#endif // NUMBERVAL_H
