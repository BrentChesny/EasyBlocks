#include "userstatementdialog.h"
#include "ui_userstatementdialog.h"

#include <qalgorithms.h>
#include <QDebug>

UserStatementDialog::UserStatementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserStatementDialog)
{
    ui->setupUi(this);
    ui->horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);

    addItem();
}

UserStatementDialog::~UserStatementDialog()
{
    delete ui;
}

QString UserStatementDialog::getParamDescription()
{
    QString desc = "";

    for (int i = 0; i < _types.size(); ++i) {
        if (_types.at(i) != -1)
            desc += " %p ";
        else
            desc += _edits.at(i)->text();
    }

    return desc;
}

QList<Block::ParamType> UserStatementDialog::getParamTypes()
{
    QList<Block::ParamType> types;
    for (int i = 0; i < _types.size(); ++i) {
        if (_types.at(i) != -1)
            types.append(_types.at(i));
    }
    return types;
}

QStringList UserStatementDialog::getParamNames()
{
    QStringList names;

    for (int i = 0; i < _types.size(); ++i) {
        if (_types.at(i) != -1)
            names.append(_edits.at(i)->text());
    }

    return names;
}

void UserStatementDialog::on_labelBtn_clicked()
{
    addItem();
}

void UserStatementDialog::on_numBtn_clicked()
{
    addItem(Block::NUMBER_EXPRESSION);
}

void UserStatementDialog::on_textBtn_clicked()
{
    addItem(Block::STRING_EXPRESSION);
}

void UserStatementDialog::on_boolBtn_clicked()
{
    addItem(Block::BOOLEAN_EXPRESSION);
}


void UserStatementDialog::on_numVarBtn_clicked()
{
    addItem(Block::NUMBER_VAR);
}

void UserStatementDialog::on_textVarBtn_clicked()
{
    addItem(Block::STRING_VAR);
}

void UserStatementDialog::on_boolVarBtn_clicked()
{
    addItem(Block::BOOLEAN_VAR);
}

void UserStatementDialog::on_numListBtn_clicked()
{
    addItem(Block::NUMBER_LIST);
}

void UserStatementDialog::on_textListBtn_clicked()
{
    addItem(Block::STRING_LIST);
}

void UserStatementDialog::on_boolListBtn_clicked()
{
    addItem(Block::BOOLEAN_LIST);
}

void UserStatementDialog::addItem(Block::ParamType type)
{
    QColor color;
    if (type == -1)
        color = Qt::white;
    else
        color = BlockColors::getColor(type);

    QLineEdit* edit = new QLineEdit(QString("label%1").arg(QString::number(_edits.size() + 1)));
    edit->setFixedWidth(50);
    edit->setStyleSheet(QString("QLineEdit{background:rgba(%1,%2,%3, 100%);}").arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue())));
    _edits.append(edit);

    ui->horizontalLayout->addWidget(edit);
    edit->setFocus();

    _types.append(type);
}
