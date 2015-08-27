#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGridLayout>

#include "screenview.h"
#include "programmodel.h"
#include "applicationgui/variablevaluewidget.h"

namespace Ui {
class ProgramWindow;
}

class ProgramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgramWindow(ProgramModel* model, QWidget *parent = 0);
    virtual ~ProgramWindow();

protected:
    void closeEvent(QCloseEvent* event);

signals:
    void closed();

public slots:
    void update();
    void outputReceived(const QString& output);
    void inputRequestReceived();
    void sendAnswer();

private slots:
    void on_actionShow_Variables_triggered();

private:
    Ui::ProgramWindow *ui;

    ProgramModel* _model;

    bool _askingInput;

    VariableValueWidget* _varWidget;
};

#endif // PROGRAMWINDOW_H
