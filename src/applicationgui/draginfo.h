#ifndef DRAGINFO_H
#define DRAGINFO_H

#include <QPoint>

class BlockReprView;
class BlockRepr;

/**
 * @brief DragInfo is used for passing information when using drag and drop
 *
 * @author Brecht Vandevoort
 */
class DragInfo
{
public:
    /**
     * @brief Constructor
     */
    DragInfo() : _blockRepr(NULL), _dropSuccessful(false), _keepOriginal(true) {}

    /**
     * @brief Destructor
     */
    ~DragInfo() {}

    /**
     * @brief Sets the BlockRepr
     * @param blockRepr The blockRepr to set
     */
    void setBlockRepr(BlockRepr* blockRepr) {_blockRepr = blockRepr;}

    /**
     * @brief Returns the BlockRepr
     * @return Pointer to the BlockRepr
     */
    BlockRepr* getBlockRepr() const {return _blockRepr;}

    /**
     * @brief Sets whether the drop was successful or not
     * @param successful True if the drop was successful, false if not
     */
    void setDropSuccessful(bool successful = true) {_dropSuccessful = successful;}

    /**
     * @brief Returns whether the drop was successful
     * @return True if the drop was successful, false if not
     */
    bool getDropSuccessful() const {return _dropSuccessful;}

    /**
     * @brief Sets whether or not the original BlockRepr needs to stay
     * @param keep If true, the original BlockRepr in the drag will be kept
     */
    void setKeepOriginal(bool keep) {_keepOriginal = keep;}

    /**
     * @brief Returns whether or not the original BlockReprView needs to stay
     * @return True if the original BlockReprView needs to be kept
     */
    bool getKeepOriginal() const {return _keepOriginal;}

    /**
     * @brief setTopLeft
     * @param topLeft
     */
    void setTopLeft(QPoint topLeft) {_topLeft = topLeft;}

    QPoint getTopLeft() const {return _topLeft;}

private:
    BlockRepr* _blockRepr;

    bool _dropSuccessful;

    bool _keepOriginal;

    QPoint _topLeft;
};

#endif // DRAGINFO_H
