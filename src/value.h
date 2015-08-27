#ifndef VALUE_H
#define VALUE_H

#include <QString>

/**
 * @brief The Value class
 *
 * @author Brent Chesny
 */
class Value
{
public:
    /**
     * @brief The DataType enum
     */
    enum DataType {NUMBER, STRING, BOOLEAN};

    /**
     * @brief Constructor method
     */
    Value();

    /**
     * @brief Destructor method
     */
    virtual ~Value() {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    virtual DataType getDataType() const = 0;

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    virtual double toDouble() const = 0;

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    virtual QString toString() const = 0;

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    virtual bool toBool() const = 0;

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    virtual Value* copy() const = 0;
};

#endif // VALUE_H
