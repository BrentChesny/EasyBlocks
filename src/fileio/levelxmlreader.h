#ifndef LEVELXMLREADER_H
#define LEVELXMLREADER_H

#include <QDomElement>

#include "../levelhandler.h"

/**
 * @brief The LevelXMLReader class
 *
 * @author Brecht Vandevoort
 */
class LevelXMLReader
{
public:
    /**
     * @brief Constructor
     */
    LevelXMLReader();

    /**
     * @brief Reads the file to create a LevelHandler
     * @param path Path to the file
     * @return True if successful
     */
    bool readFromFile(const QString& path);

    /**
     * @brief Returns the created LevelHandler
     * @return Pointer to the created LevelHandler
     */
    LevelHandler* getLevelHandler() const {return _levelHandler;}

private:
    LevelHandler* _levelHandler;

    bool createLevelHandler(const QDomElement& element);
};

#endif // LEVELXMLREADER_H
