#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>

/**
 * @brief The SizeDialog class
 *
 * @author Brent Chesny
 */
class SizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SizeDialog(QSize* size, QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent* event);

signals:

public slots:
    void accept();

private:
    QSize* _size;
    QLabel* _heightLabel;
    QLineEdit* _heightEdit;
    QLabel* _widthLabel;
    QLineEdit* _widthEdit;
    QDialogButtonBox* _buttons;

};

#endif // SIZEDIALOG_H
