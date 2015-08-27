#ifndef SCREEN_H
#define SCREEN_H

#include <QSize>
#include <QPixmap>
#include <QColor>

/**
 * @brief The Screen class
 *
 * @author Brent Chesny
 */
class Screen
{
public:
    /**
     * @brief Constructor method
     */
    Screen();

    /**
     * @brief Destructor
     */
    ~Screen();

    /**
     * @brief Returns the color of the screen
     * @return The color of the screen
     */
    QColor getColor() const { return _color; }

    /**
     * @brief Setter for the backgroundcolor
     * @param color The background color
     */
    void setColor(QColor color);

    /**
     * @brief Returns the size of the screen
     * @return The size of the screen
     */
    QSize getSize() const { return _size; }

    /**
     * @brief Setter for the size
     * @param size The size
     */
    void setSize(QSize size) { _size = size; }

    /**
     * @brief Returns the background of the screen
     * @return The background of the screen.
     */
    QPixmap* getBackground() const { return _background; }

    /**
     * @brief Setter for the background image
     * @param pixmap The background image
     */
    void setBackground(QPixmap* pixmap);

private:
    QSize _size;

    QColor _color;

    QPixmap* _background;
};

#endif // SCREEN_H
