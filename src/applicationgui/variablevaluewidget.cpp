#include "variablevaluewidget.h"

#include <QGridLayout>
#include <QLabel>

VariableValueWidget::VariableValueWidget(ProgramModel* model) :
    _model(model)
{
    connect(_model, SIGNAL(update()), this, SLOT(update()));
    init();
}

void VariableValueWidget::init()
{
    QGridLayout* layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    QtVariantPropertyManager *variantManager = new QtVariantPropertyManager(this);
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    QtTreePropertyBrowser *variantEditor = new QtTreePropertyBrowser();
    variantEditor->setHeaderVisible(false);
    layout->addWidget(variantEditor);

    // global vars
    QList<Variable*> vars = _model->getVarTable()->getVariables();
    QList<ValueList*> lists = _model->getVarTable()->getLists();
    for (int i = 0; i < vars.size(); ++i) {
        QtVariantProperty* prop = variantManager->addProperty(QVariant::String, vars.at(i)->getName());
        prop->setValue(vars.at(i)->getValue()->toString());
        variantEditor->addProperty(prop);
        _globalVars.append(prop);
    }
    for (int i = 0; i < lists.size(); ++i) {
        QtVariantProperty* prop = variantManager->addProperty(QVariant::String, lists.at(i)->getName());
        QStringList items;
        for (int j = 0; j < lists.at(i)->getSize(); ++j) {
            items.append(lists.at(i)->getValueAt(j)->toString());
        }
        prop->setValue(items.join(", "));
        variantEditor->addProperty(prop);
        _globalLists.append(prop);
    }

    // sprite vars
    QList<Sprite*> sprites = _model->getSprites();
    for (int i = 0; i < sprites.size(); ++i) {
        QList<QtVariantProperty*> varProps;
        QList<QtVariantProperty*> listProps;
        QList<Variable*> vars = sprites.at(i)->getVarTable()->getSpriteVars()->getVariables();
        QList<ValueList*> lists = sprites.at(i)->getVarTable()->getSpriteVars()->getLists();
        for (int j = 0; j < vars.size(); ++j) {
            QtVariantProperty* prop = variantManager->addProperty(QVariant::String, vars.at(j)->getName());
            prop->setValue(vars.at(i)->getValue()->toString());
            variantEditor->addProperty(prop);
            varProps.append(prop);
        }
        for (int j = 0; j < lists.size(); ++j) {
            QtVariantProperty* prop = variantManager->addProperty(QVariant::String, lists.at(j)->getName());
            QStringList items;
            for (int k = 0; k < lists.at(j)->getSize(); ++k) {
                items.append(lists.at(j)->getValueAt(k)->toString());
            }
            prop->setValue(items.join(", "));
            variantEditor->addProperty(prop);
            listProps.append(prop);
        }
        _localVars.append(varProps);
        _localLists.append(listProps);
    }

    variantEditor->setFactoryForManager(variantManager, variantFactory);
    variantEditor->setPropertiesWithoutValueMarked(true);
    variantEditor->setRootIsDecorated(false);
    variantEditor->setFocusPolicy(Qt::NoFocus);
}

void VariableValueWidget::update()
{
    // global vars
    QList<Variable*> vars = _model->getVarTable()->getVariables();
    QList<ValueList*> lists = _model->getVarTable()->getLists();
    for (int i = 0; i < vars.size(); ++i) {
        _globalVars.at(i)->setValue(vars.at(i)->getValue()->toString());
    }
    for (int i = 0; i < lists.size(); ++i) {
        QStringList items;
        for (int j = 0; j < lists.at(i)->getSize(); ++j) {
            items.append(lists.at(i)->getValueAt(j)->toString());
        }
        _globalLists.at(i)->setValue(items.join(", "));
    }

    // sprite vars
    QList<Sprite*> sprites = _model->getSprites();
    for (int i = 0; i < sprites.size(); ++i) {
        QList<Variable*> vars = sprites.at(i)->getVarTable()->getSpriteVars()->getVariables();
        QList<ValueList*> lists = sprites.at(i)->getVarTable()->getSpriteVars()->getLists();
        for (int j = 0; j < vars.size(); ++j) {
            _localVars.at(i).at(j)->setValue(vars.at(j)->getValue()->toString());
        }
        for (int j = 0; j < lists.size(); ++j) {
            QStringList items;
            for (int k = 0; k < lists.at(j)->getSize(); ++k) {
                items.append(lists.at(j)->getValueAt(k)->toString());
            }
            _localLists.at(i).at(j)->setValue(items.join(", "));
        }
    }
}
