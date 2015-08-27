#include "edituserstatementbutton.h"

#include <QFont>

EditUserStatementButton::EditUserStatementButton(int index, QString text, QObject *parent) :
    QPushButton(text), _index(index)
{
    setFixedHeight(23);
    QFont f("Arial", 11);
    f.setPixelSize(11);
    setFont(f);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::transparent);
    setPalette(palette);
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

void EditUserStatementButton::btnClicked()
{
    emit clicked(_index);
}
