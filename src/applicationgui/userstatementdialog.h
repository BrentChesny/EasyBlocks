#ifndef USERSTATEMENTDIALOG_H
#define USERSTATEMENTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolButton>

#include "../block.h"
#include "blockcolors.h"

namespace Ui {
class UserStatementDialog;
}

class UserStatementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserStatementDialog(QWidget *parent = 0);
    ~UserStatementDialog();

    QString getParamDescription();
    QList<Block::ParamType> getParamTypes();
    QStringList getParamNames();

private slots:
    void on_labelBtn_clicked();

    void on_numBtn_clicked();

    void on_textBtn_clicked();

    void on_boolBtn_clicked();

    void on_numVarBtn_clicked();

    void on_textVarBtn_clicked();

    void on_boolVarBtn_clicked();

    void on_numListBtn_clicked();

    void on_textListBtn_clicked();

    void on_boolListBtn_clicked();

private:
    Ui::UserStatementDialog *ui;

    QList<QLineEdit*> _edits;
    QList<Block::ParamType> _types;

    void addItem(Block::ParamType type = (Block::ParamType) -1);
};

#endif // USERSTATEMENTDIALOG_H
