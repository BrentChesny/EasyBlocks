#ifndef BOOLEANVALUE_H
#define BOOLEANVALUE_H

#include "value.h"

#include <QString>

/**
 * @brief The BooleanValue class
 *
 * @author Brent Chesny
 */
class BooleanValue : public Value
{
public:
    /**
     * @brief Constructor method
     */
    BooleanValue(bool value) : _value(value) {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    DataType getDataType() const { return BOOLEAN; }

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    double toDouble() const { return _value ? 1.0 : 0.0; }

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    QString toString() const { return _value ? QString("true") : QString("false"); }

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    bool toBool() const { return _value; }

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    Value* copy() const;

private:
    bool _value;
};


#endif // BOOLEANVALUE_H
