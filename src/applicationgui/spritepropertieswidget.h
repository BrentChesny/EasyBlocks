#ifndef SPRITEPROPERTIESWIDGET_H
#define SPRITEPROPERTIESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

#include "../easyblocksmodel.h"
#include "propertybrowser/qtpropertymanager.h"
#include "propertybrowser/qtvariantproperty.h"
#include "propertybrowser/qttreepropertybrowser.h"

/**
 * @brief The SpritePropertiesWidget class
 *
 * @author Brent Chesny
 */
class SpritePropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpritePropertiesWidget(EasyBlocksModel* model, QWidget *parent = 0);

signals:

public slots:
    void updateValues();
    void valueChanged(QtProperty* property, QVariant value);

private:
    EasyBlocksModel* _model;
    QVBoxLayout* _layout;

    QtVariantProperty* _nameProperty;
    QtVariantProperty* _posProperty;
    QtVariantProperty* _sizeProperty;
    QtVariantProperty* _rotationProperty;

    void init();
    void createPropertyBrowser();
};

#endif // SPRITEPROPERTIESWIDGET_H
