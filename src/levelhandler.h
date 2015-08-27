#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include <QStringList>

/**
 * @brief The LevelHandler class
 *
 * @author Brecht Vandevoort
 */
class LevelHandler
{
public:
    /**
     * @brief Constructor
     */
    LevelHandler(bool defaultVisible = true);

    /**
     * @brief Sets the default visibility of a block
     * @param visible If true, blocks will be visible by default
     */
    void setDefault(bool visible) {_defaultVisible = visible;}

    /**
     * @brief Registers a block to be visible
     * @param id Id of the block to register
     */
    void registerVisible(const QString& id);

    /**
     * @brief Registers a block to be invisible
     * @param id Id of the block to register
     */
    void registerInvisible(const QString& id);

    /**
     * @brief Returns whether or not a block is visible
     * @param id Id of the block to check
     * @return True if the block is visible, false if not
     */
    bool isVisible(const QString& id) const;

private:
    QStringList _visible;
    QStringList _invisible;

    bool _defaultVisible;
};

#endif // LEVELHANDLER_H
