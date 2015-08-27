#ifndef VARIABLEWIDGET_H
#define VARIABLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "../easyblocksmodel.h"

class VariableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VariableWidget(EasyBlocksModel* model, QWidget *parent = 0);

    ~VariableWidget();

public slots:
    void addVariable();
    void update();

private:
    EasyBlocksModel* _model;
    QVBoxLayout* _layout;
    QHBoxLayout* _btnLayout;
    QGraphicsView* _view;
    QGraphicsScene* _scene;

    void init();
    void createButtons();
    void draw();
};

#endif // VARIABLEWIDGET_H
