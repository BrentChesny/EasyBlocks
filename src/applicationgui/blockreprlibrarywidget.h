#ifndef BLOCKREPRLIBRARYWIDGET_H
#define BLOCKREPRLIBRARYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include "categorybutton.h"
#include "../easyblocksmodel.h"

/**
 * @brief The BlockReprLibraryWidget class
 *
 * @author Brent Chesny
 */
class BlockReprLibraryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlockReprLibraryWidget(EasyBlocksModel* model, QWidget *parent = 0);

    ~BlockReprLibraryWidget();

signals:
    void selectedUserFunc(int index);

public slots:
    void buttonClicked(QString cat);
    void addBlock();
    void editUserFunc(int index);

private:    
    EasyBlocksModel* _model;

    QList<CategoryButton*> _buttons;

    QGridLayout* _gridLayout;

    QVBoxLayout* _verticalLayout;

    QGraphicsView* _view;
    QGraphicsScene* _scene;

    QString _currentCat;

    void init();
    void setupButtons();
    void setupView();
    void draw();
    void setActiveCategory(QString cat);

    QGraphicsProxyWidget* _addBlockBtnProxy;
};

#endif // BLOCKREPRLIBRARYWIDGET_H
