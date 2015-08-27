#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include <QPushButton>

/**
 * @brief The CategoryButton class
 *
 * @author Brent Chesny
 */
class CategoryButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     * @param parent Parent object
     */
    explicit CategoryButton(QString cat, QString text, QWidget *parent = 0);

    /**
     * @brief Setter for the category name
     * @param cat The category name
     */
    void setCategoryName(QString cat) { _cat = cat; }

    /**
     * @brief Getter for the category name
     * @return The category name
     */
    QString getCategoryName() const { return _cat; }

signals:
    void clicked(QString);

public slots:
    void btnClicked();

private:
    QString _cat;

};

#endif // CATEGORYBUTTON_H
