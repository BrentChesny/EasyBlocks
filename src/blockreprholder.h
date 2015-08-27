#ifndef BLOCKREPRHOLDER_H
#define BLOCKREPRHOLDER_H

#include <QObject>

class BlockRepr;
class Project;

/**
 * @brief The BlockReprHolder class,
 *
 * @author Brecht Vandevoort
 */
class BlockReprHolder : public QObject
{
    Q_OBJECT
public:
    BlockReprHolder();

    /**
     * @brief Copy constructor
     * @param holder The holder to copy
     */
    BlockReprHolder(const BlockReprHolder &holder);

    /**
     * @brief Destructor
     */
    virtual ~BlockReprHolder();

    /**
     * @brief Adds a block
     * @param block The BlockRepr to add
     */
    void addBlock(BlockRepr* block);

    /**
     * @brief Removes a block
     * @param block The block to remove
     * @return True if the block was removed, false if not
     */
    bool removeBlock(BlockRepr* block);

    /**
     * @brief Returns the list of blocks this UserStatementRepr contains
     * @return The list of blocks this UserStatementRepr contains
     */
    QList<BlockRepr*> getBlocks() const {return _blocks;}

    /**
     * @brief Checks this sprite for variables which are no longer valid and deletes them
     * @param project Pointer to the Project
     */
    void checkExistance(Project* project);

signals:
    /**
     * @brief Signal is sent every time the blocks change
     */
    void blocksUpdated();

public slots:

private:
    QList<BlockRepr*> _blocks;
};

#endif // BLOCKREPRHOLDER_H
