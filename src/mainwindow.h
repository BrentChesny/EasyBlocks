#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QAction>
#include <QCoreApplication>
#include <QTranslator>

#include "easyblocksmodel.h"
#include "applicationgui/blockreprlibrarywidget.h"
#include "applicationgui/workspacewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QCoreApplication* app, QWidget *parent = 0);
    ~MainWindow();

    void openProject(const QString &path);

protected:
    void closeEvent(QCloseEvent* event);

public slots:
    void disableToolsBasedOnTab(int index);
    void update();
    void newAction();
    void openAction();
    void saveAction();
    void saveasAction();
    void loadConfigAction();
    void resetConfigAction();
    void runAction();
    void stopAction();
    void pauseAction();
    void programStopped();
    void translateEnglish();
    void translateDutch();

private:
    Ui::MainWindow *ui;

    EasyBlocksModel* _model;

    QHBoxLayout* _mainLayout;
    BlockReprLibraryWidget* _blockReprLibrary;
    WorkspaceWidget* _workspace;

    QAction* _newAction;
    QAction* _openAction;
    QAction* _saveAction;
    QAction* _saveasAction;
    QAction* _loadConfigAction;
    QAction* _runAction;
    QAction* _stopAction;
    QAction* _pauseAction;
    QAction* _zoominAction;
    QAction* _zoomoutAction;

    Program* _program;

    bool _unsaved;

    QCoreApplication* _application;
    QTranslator _trDutch;

    void setupUi();
    void createToolbar();
    void createMenubar();
    void renewBlockLibraryWidget();
    void setTitle();
    int showSaveChangesDialog();

    void reload();
};

#endif // MAINWINDOW_H
