#ifndef STRINGCONSTANTBLOCKREPRVIEW_H
#define STRINGCONSTANTBLOCKREPRVIEW_H

#include <QLineEdit>
#include <QGraphicsProxyWidget>

#include "blockreprview.h"

class ConstantBlockRepr;

/**
 * @brief The StringConstantBlockReprView class
 *
 * @author Brecht Vandevoort
 */
class StringConstantBlockReprView : public BlockReprView
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param blockRepr The ConstantBlockRepr this view is based on
     */
    StringConstantBlockReprView(ConstantBlockRepr* blockRepr, QGraphicsItem *parent = 0);

public slots:
    /**
     * @brief This function is called when the text changes
     */
    void stringChanged();

private:
    ConstantBlockRepr* _constantBlockRepr;
    QLineEdit* _lineEdit;
    QGraphicsProxyWidget* _proxy;
};

#endif // STRINGCONSTANTBLOCKREPRVIEW_H
