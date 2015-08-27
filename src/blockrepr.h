#ifndef BLOCKREPR_H
#define BLOCKREPR_H

#include "block.h"

#include <QStringList>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QFont>
#include <QList>
#include <QDebug>

class ParamRepr;
class BlockReprHolder;
class Project;

/**
 * @brief The BlockRepr class
 *
 * @author Brent Chesny
 */
class BlockRepr : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     */
    BlockRepr(Block* block, bool locked = false);

    /**
     * @brief Copy constructor method
     */
    BlockRepr(const BlockRepr& repr);

    /**
     * @brief Destructor method
     */
    virtual ~BlockRepr();

    /**
     * @brief Returns a copy of this BlockRepr
     * @return A copy of this BlockRepr
     */
    virtual BlockRepr* copy();

    /**
     * @brief Returns the id of this block
     * @return The id of this block
     */
    QString getId() const { return _id; }

    /**
     * @brief Sets the position of this block
     * @param pos The new position
     */
    void setPosition(QPoint pos) { _position = pos; }

    /**
     * @brief Returns the position
     * @return The position of this block
     */
    QPoint getPosition() const { return _position; }

    /**
     * @brief Sets the parent BlockRepr of this block
     * @param parent The parent BlockRepr of this block
     */
    void setParent(BlockRepr* parent) { _parent = parent; _holderParent = NULL; }

    /**
     * @brief Sets the parent BlockReprHolder of this block
     * @param parent The parent BlockReprHolder of this block
     */
    void setHolderParent(BlockReprHolder* parent);

    /**
     * @brief Returns the current BlockReprHolder of this block
     * @return The BlockReprHolder parent of this block
     */
    BlockReprHolder* getHolderParent() const { return _holderParent; }

    /**
     * @brief Returns the current BlockRepr parent of this block
     * @return The BlockRepr parent of this block
     */
    BlockRepr* getParent() const { return _parent; }

    /**
     * @brief Returns the total size of the block, including the following blocks
     * @return The total size of the block, including the following blocks
     */
    virtual QSize getTotalSize();

    /**
     * @brief Returns the size of this block, the following blocks excluded
     * @return The size of this block
     */
    virtual QSize getSize();

    /**
     * @brief Returns the size of the header of the block
     * @return The size of the header of the block
     */
    virtual QSize getHeaderSize();

    /**
     * @brief Returns the size of a description for a body
     * @param index The index of the body you want the description for
     * @return The size of the desired body description
     */
    QSize getBodyDescriptionSize(int index);

    /**
     * @brief Returns the size of a body
     * @param index The index of the body you want size for
     * @return The size of the desired body
     */
    QSize getBodySize(int index);

    /**
     * @brief Returns the size of a description for a param
     * @param index The index of the param you want the description for
     * @return The size of the desired param description
     */
    QSize getParamDescriptionsize(int index);

    /**
     * @brief Returns the size of a param
     * @param index The index of the param you want size for
     * @return The size of the desired param
     */
    QSize getParamSize(int index);

    /**
     * @brief Returns if a body fits on a certain position
     * @param repr The block to fit
     * @param index The index of the place to fit the block in
     * @return True if a body fits on a certain position
     */
    bool doesBodyFit(BlockRepr* repr, int index);

    /**
     * @brief Places a body on a certain position
     * @param repr The block to place
     * @param index The index of the position to place the block in
     * @return True if the block was placed successfully
     */
    bool placeBody(BlockRepr* repr, int index);

    /**
     * @brief Returns if a param fits on a certain position
     * @param repr The param to fit
     * @param index The index of the place to fit the param in
     * @return True if a param fits on a certain position
     */
    bool doesParamFit(BlockRepr* repr, int index);

    /**
     * @brief Places a param on a certain position
     * @param repr The param to place
     * @param index The index of the position to place the param in
     * @return True if the param was placed successfully
     */
    bool placeParam(BlockRepr* repr, int index);

    /**
     * @brief Sets the next statement
     * @param repr The statement to set as next block
     * @return True if succeeded
     */
    bool placeNextStatement(BlockRepr* repr);

    /**
     * @brief Removes a body
     * @param index The index of the body to remove
     * @return true if succeeded
     */
    bool removeBody(int index);

    /**
     * @brief Removes a param
     * @param index The index of the param to remove
     * @return True if succeeded
     */
    bool removeParam(int index);

    /**
     * @brief Removes the statement following this block
     * @return True if succeeded
     */
    bool removeNextStatement();

    /**
     * @brief Removes this block from its parent
     * @return True if succeeded
     */
    bool removeFromParent();

    /**
     * @brief Removes a given block from this block
     * @param repr The block to remove
     * @return True if succeeded
     */
    bool remove(BlockRepr* repr);

    /**
     * @brief Returns the number of bodies
     */
    int getNumBodies() const;

    /**
     * @brief Returns the number of params
     */
    int getNumParams() const;

    /**
     * @brief Returns a pointer to the body at index
     * @param index The index of the body
     * @return The block at index
     */
    BlockRepr* getBody(int index) const;

    /**
     * @brief Returns a pointer to the param at index
     * @param index The index of the param
     * @return The param at index
     */
    BlockRepr* getParam(int index) const;

    /**
     * @brief Returns the statement following this block
     * @return The statement following this block, as a BlockRepr pointer
     */
    BlockRepr* getNextStatement() { return _nextBlock; }

    /**
     * @brief Returns the type of the block
     * @return The type of the block
     */
    Block::ParamType getReturnType() const { return _returnType; }

    /**
     * @brief Returns the type of the param at index
     * @param index The index of the param
     * @return The type of the param at index
     */
    Block::ParamType getParamType(int index) const;

    /**
     * @brief Returns the parameter descriptions
     * @return A list of parameter descriptions
     */
    QStringList getParamDescriptions() const { return _paramLabels; }

    /**
     * @brief Returns the body descriptions
     * @return A list of body descriptions
     */
    QStringList getBodyDescriptions() const { return _bodyLabels; }

    /**
     * @brief Returns the position for the param at index
     * @param index The index of the param
     * @return The position of the param at index
     */
    QPoint getParamPosition(int index);

    /**
     * @brief Returns the position for the body at index
     * @param index The index of the body
     * @return The position of the body at index
     */
    QPoint getBodyPosition(int index);

    /**
     * @brief Returns the position for the param description at index
     * @param index The index of the param description
     * @return The position of the param description at index
     */
    QPoint getParamDescriptionPosition(int index);

    /**
     * @brief Returns the position for the body description at index
     * @param index The index of the body description
     * @return The position of the body description at index
     */
    QPoint getBodyDescriptionPosition(int index);

    /**
     * @brief Returns the position of the next statement
     * @return The position of the next statement
     */
    QPoint getNextStatementPosition();

    /**
     * @brief Reverts this block to a previous state
     */
    void revert();

    /**
     * @brief Sets or resets a lock on this block, no longer allowing it to accept other blocks
     * @param locked True to set the lock or false to reset the lock
     */
    void setLock(bool locked = true) {_isLocked = locked;}

    /**
     * @brief Returns true if the block is locked
     * @return True if this block is locked
     */
    bool isLocked() const {return _isLocked;}

    /**
     * @brief Returns true if this block is an instance of ConstantBlockRepr
     * @return True if this block is an instance of ConstantBlockRepr
     */
    virtual bool isConstantBlockRepr() const { return false; }

    /**
     * @brief Returns true if this block is an instance of VarBlockRepr
     * @return True if this block is an instance of VarBlockRepr
     */
    virtual bool isVarBlockRepr() const { return false; }

    /**
     * @brief Returns true if this block is an instance of SpriteBlockRepr
     * @return True if this block is an instance of SpriteBlockRepr
     */
    virtual bool isSpriteBlockRepr() const { return false; }

    /**
     * @brief Returns true if this block is an instance of UserStatementRepr
     * @return True if this block is an instance of UserStatementRepr
     */
    virtual bool isUserStatementRepr() const { return false; }

    /**
     * @brief Runs a check on this block to remove invalid blocks.
     * @param project Pointer to the current project
     */
    virtual void checkExistance(Project* project);

    /**
     * @brief The font used in the blocks
     */
    static QFont FONT;

    static const int MARGIN;

    static const int MARGIN_HORIZONTAL;

    static const int LEFT_GUTTER;

    static const int FOOTER_HEIGHT;

    static const int FOOTER_WIDTH;

    static const QSize HOLDER_SIZE;

protected:
    BlockRepr(Block::ParamType type, QString name, bool locked = false, bool isVar = true);
    BlockRepr(Block::ParamType type, bool locked = false);

    void setParamLabels(QStringList paramLabels);
    void setParamLabels(QString paramLabels);
    void setParamTypes(QList<Block::ParamType> paramTypes);

    void emitBlockUpdated(bool param, bool body, bool next);

signals:
    void blockUpdated();

public slots:
    void duplicateBlock();
    void deleteBlock();

private:
    QString _id;
    BlockRepr* _parent;
    BlockReprHolder* _holderParent;
    Block::ParamType _returnType;
    QStringList _paramLabels;
    QList<ParamRepr*> _params;
    QStringList _bodyLabels;
    QList<BlockRepr*> _bodies;
    QPoint _position;
    BlockRepr* _nextBlock;
    bool _lastRemovedWasParam;
    int _lastRemovedIndex;
    BlockRepr* _lastRemoved;
    bool _isLocked;

    QRect getFontRect(QString string);
    QSize getParamListSize();

    void revertToParent();

    void calculateSizes(bool param, bool body, bool next);
    void calculateTotalSize();
    void calculateSize();
    void calculateParamListSize();
    void calculateHeaderSize();

    void calculatePositions(bool param, bool body, bool next);
    void calculateParamPositions();
    void calculateParamLabelPositions();

    // Sizes
    QSize _totalSize;
    QSize _size;
    QSize _paramListSize;
    QSize _headerSize;
    QList<QPoint> _paramPositions;
    QList<QPoint> _paramLabelPositions;
};

#endif // BLOCKREPR_H
