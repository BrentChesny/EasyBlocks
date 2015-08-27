#ifndef VARIABLEVALUEWIDGET_H
#define VARIABLEVALUEWIDGET_H

#include <QWidget>
#include "../programmodel.h"

#include "propertybrowser/qtpropertymanager.h"
#include "propertybrowser/qtvariantproperty.h"
#include "propertybrowser/qttreepropertybrowser.h"

class VariableValueWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     */
    VariableValueWidget(ProgramModel* model);

public slots:
    void update();

private:
    ProgramModel* _model;

    QList<QtVariantProperty*> _globalVars;
    QList<QtVariantProperty*> _globalLists;
    QList<QList<QtVariantProperty*> > _localVars;
    QList<QList<QtVariantProperty*> > _localLists;

    void init();
};

#endif // VARIABLEVALUEWIDGET_H
