#ifndef BLOCKMIMEDATA_H
#define BLOCKMIMEDATA_H

#include <QMimeData>
#include "draginfo.h"

/**
 * @brief The BlockMimeData class
 *
 * @author Brecht Vandevoort
 */
class BlockMimeData : public QMimeData
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    BlockMimeData() {_dragInfo = new DragInfo();}

    /**
     * @brief Destructor
     */
    ~BlockMimeData() { delete _dragInfo;}

    /**
     * @brief Returns the DragInfo
     * @return The DragInfo containing information about this drag
     */
    DragInfo* getDragInfo() const {return _dragInfo;}

private:
    DragInfo* _dragInfo;
};

#endif // BLOCKMIMEDATA_H
