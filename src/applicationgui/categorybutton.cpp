#include "categorybutton.h"

CategoryButton::CategoryButton(QString cat, QString text, QWidget *parent) :
    QPushButton(text, parent), _cat(cat)
{
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

void CategoryButton::btnClicked()
{
    emit clicked(_cat);
}
