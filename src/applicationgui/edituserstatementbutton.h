#ifndef EDITUSERSTATEMENTBUTTON_H
#define EDITUSERSTATEMENTBUTTON_H

#include <QPushButton>

class EditUserStatementButton : public QPushButton
{
    Q_OBJECT
public:
    explicit EditUserStatementButton(int index, QString text, QObject *parent = 0);

signals:
    void clicked(int index);
public slots:
    void btnClicked();
private:
    int _index;
};

#endif // EDITUSERSTATEMENTBUTTON_H
