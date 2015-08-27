#ifndef NUMBERCONSTANTBLOCKREPRVIEW_H
#define NUMBERCONSTANTBLOCKREPRVIEW_H

#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QDoubleValidator>

#include "blockreprview.h"

class ConstantBlockRepr;

/**
 * @brief The NumberConstantBlockReprView class
 *
 * @author Brecht Vandevoort
 */
class NumberConstantBlockReprView : public BlockReprView
{
    Q_OBJECT
public:
    NumberConstantBlockReprView();
    /**
     * @brief Constructor
     * @param blockRepr The ConstantBlockRepr this view is based on
     */
    NumberConstantBlockReprView(ConstantBlockRepr* blockRepr, QGraphicsItem *parent = 0);

public slots:
    /**
     * @brief This function is called when the text changes
     */
    void numberChanged();

private:
    ConstantBlockRepr* _constantBlockRepr;
    QLineEdit* _lineEdit;
    QGraphicsProxyWidget* _proxy;
    QDoubleValidator* _validator;
};

#endif // NUMBERCONSTANTBLOCKREPRVIEW_H
