#ifndef VARIABLEDIALOG_H
#define VARIABLEDIALOG_H

#include "../block.h"

#include <QDialog>

namespace Ui {
class VariableDialog;
}

/**
 * @brief The VariableDialog class
 *
 * @author Brent Chesny
 */
class VariableDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     * @param parent Parent widget
     */
    explicit VariableDialog(QWidget *parent = 0);

    /**
     * @brief Destructor method
     */
    virtual ~VariableDialog();

    /**
     * @brief Returns the variable type
     * @return The variable type
     */
    Block::ParamType getType() const { return _type; }

    /**
     * @brief Returns of the variable is global
     * @return True if the variable is global
     */
    bool isGlobal() const { return _global; }

    /**
     * @brief Returns the var name
     * @return The variable name
     */
    QString getName() const { return _name; }

public slots:
    void accept();

private:
    bool _global;
    bool _list;
    Block::ParamType _type;
    QString _name;

    Ui::VariableDialog *ui;
};

#endif // VARIABLEDIALOG_H
