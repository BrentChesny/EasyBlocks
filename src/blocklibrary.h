#ifndef BLOCKLIBRARY_H
#define BLOCKLIBRARY_H

#include <QList>
#include <QString>

#include "block.h"

class BlockReprLibrary;

/**
 * @brief The BlockLibrary class
 *
 * @author Brecht Vandevoort
 */
class BlockLibrary
{
public:
    /**
     * @brief Constructor
     */
    BlockLibrary();

    /**
     * @brief Destructor
     */
    ~BlockLibrary();

    /**
     * @brief Registers a new Block in the Library.
     * If another block with the same id is already in the library, this function will do nothing and return false
     * @param block The block to register
     * @return True if the block is added, false if not
     */
    bool registerBlock(Block* block);

    /**
     * @brief Returns a copy of the block with the given id, or NULL if the id is not found
     * @param id The id of the block to get
     * @return A pointer to a copy of the Block with the given id
     */
    Block* getBlockInstance(QString id) const;

    /**
     * @brief Creates a BlockReprLibrary based on the blocks stored in the library
     * @return A BlockReprLibrary containing
     */
    BlockReprLibrary* createBlockReprLibrary() const;

    /**
     * @brief Returns true if the block with the given id is already in the library
     * @param id The id to check for
     * @return True if the id is already in the library
     */
    bool contains(QString id);

    /**
     * @brief Returns the block with the given id
     * @param id The id of the block you want
     * @return The block with the given id, NULL if not found
     */
    Block* get(QString id) const;

private:
    QList<Block*> _blocks;
};

#endif // BLOCKLIBRARY_H
