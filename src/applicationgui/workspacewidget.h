#ifndef WORKSPACEWIDGET_H
#define WORKSPACEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QStackedWidget>
#include <QToolButton>
#include <QMenu>

#include "blockcanvas.h"
#include "blockreprlibrarywidget.h"
#include "../easyblocksmodel.h"
#include "screencanvas.h"
#include "spritepropertieswidget.h"
#include "variablewidget.h"

class MainWindow;

/**
 * @brief The WorkspaceWidget class
 *
 * @author Brent Chesny
 */
class WorkspaceWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     * @param project The current project
     * @param parent The parent widget
     */
    explicit WorkspaceWidget(EasyBlocksModel* model, MainWindow* window, QWidget *parent = 0);

    void setBlockReprLibWidget(BlockReprLibraryWidget* widget);

signals:

public slots:
    void incrementBlockViewScale();
    void decrementBlockViewScale();
    void spriteSelectionChanged(int index);
    void setScreenSize();
    void update();
    void renewBlockCanvas();
    void userFuncSelected(int index);

private:
    EasyBlocksModel* _model;
    BlockReprLibraryWidget* _brlw;

    MainWindow* _window;
    QTabWidget* _tabs;
    QHBoxLayout* _horizontalLayout;
    QVBoxLayout* _verticalLayout;

    QGraphicsView* _blockCanvasView;
    QGraphicsView* _screenCanvasView;
    BlockCanvas* _blockCanvas;
    ScreenCanvas* _screenCanvas;
    QToolButton* _backgroundOptions;
    QMenu* _backgroundMenu;

    VariableWidget* _varwidget;
    SpritePropertiesWidget* _spriteProperties;
    QStackedWidget* _stackedWidget;
    QTabWidget* _extraBlocks;

    float _blockScale;

    void init();
};

#endif // WORKSPACEWIDGET_H
