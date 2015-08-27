#ifndef BLOCKREPRLIBRARY_H
#define BLOCKREPRLIBRARY_H

#include <QList>
#include <QStringList>

#include "blockrepr.h"
#include "levelhandler.h"

/**
 * @brief The BlockReprLibrary class
 *
 * @author Brent Chesny
 */
class BlockReprLibrary
{
public:
    /**
     * @brief Constructor method
     */
    BlockReprLibrary();

    /**
     * @brief Destructor method
     */
    ~BlockReprLibrary();

    /**
     * @brief Registers a new BlockRepr in the Library.
     * If another block with the same id is already in the library, this function will do nothing and return false
     * @param blockRepr The blockrepr to register
     * @return True if the blockrepr is added, false if not
     */
    bool registerBlock(BlockRepr* blockRepr);

    /**
     * @brief Returns a copy of the blockrepr with the given id, or NULL if the id is not found
     * @param id The id of the block to get
     * @return A pointer to a copy of the Block with the given id
     */
    BlockRepr* getBlockReprInstance(QString id) const;

    /**
     * @brief Returns a list of the categories
     * @return A list of strings of the category names
     */
    QStringList createCategoryList();

    QList<BlockRepr*> getBlocksOfCategory(QString cat);

    /**
     * @brief Returns true if the blockrepr with the given id is already in the library
     * @param id The id to check for
     * @return True if the id is already in the library
     */
    bool contains(QString id);

    /**
     * @brief Returns the blockrepr with the given id
     * @param id The id of the blockrepr you want
     * @return The block with the given id, NULL if not found
     */
    BlockRepr* get(QString id) const;

    /**
     * @brief Sets a level handler
     * @param handler The lever handler
     */
    void setLevelHandler(LevelHandler* handler);

    /**
     * @brief Returns if a block should be visible according to the levelhandler
     * @param block The block to check for
     * @return True if the block should be visible
     */
    bool isVisible(BlockRepr* block);

private:
    QList<BlockRepr*> _blockReprs;

    LevelHandler* _levelHandler;
};

#endif // BLOCKREPRLIBRARY_H
