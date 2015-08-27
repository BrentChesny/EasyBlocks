#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include "value.h"

#include <QString>

/**
 * @brief The StringValue class
 *
 * @author Brent Chesny
 */
class StringValue : public Value
{
public:
    /**
     * @brief Constructor method
     */
    StringValue(QString value) : _value(value) {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    DataType getDataType() const { return STRING; }

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    double toDouble() const { return _value.toDouble(); }

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    QString toString() const { return _value; }

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    bool toBool() const { return _value.compare("true", Qt::CaseInsensitive); }

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    Value* copy() const;

private:

    QString _value;
};

#endif // STRINGVALUE_H
