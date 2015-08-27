#include "variabledialog.h"
#include "ui_variabledialog.h"

#include <QDebug>

VariableDialog::VariableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariableDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Create Variable"));
}

VariableDialog::~VariableDialog()
{
    delete ui;
}

void VariableDialog::accept()
{
    if (ui->nameEdit->text() == "")
        return;

    _name = ui->nameEdit->text();
    _list = ui->listButton->isChecked();
    _global = ui->allButton->isChecked();
    if (ui->boolButton->isChecked())
        _type = _list ? Block::BOOLEAN_LIST : Block::BOOLEAN_VAR;
    else if (ui->textButton->isChecked())
        _type = _list ? Block::STRING_LIST : Block::STRING_VAR;
    else
        _type = _list ? Block::NUMBER_LIST : Block::NUMBER_VAR;

    QDialog::accept();
}
