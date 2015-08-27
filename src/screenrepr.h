#ifndef SCREENREPR_H
#define SCREENREPR_H

#include <QObject>
#include <QSize>
#include <QColor>
#include <QPixmap>

/**
 * @brief The ScreenRepr class
 *
 * @author Brecht Vandevoort
 */
class ScreenRepr : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent Parent Qobject
     */
    explicit ScreenRepr(QObject *parent = 0);

    /**
     * @brief Sets the size of the screen
     * @param size Size to set
     */
    void setSize(QSize size) {_size = size; setChanged();}

    /**
     * @brief Returns the size of the screen
     * @return Size of the screen
     */
    QSize getSize() const {return _size;}

    /**
     * @brief Sets the backgroundcolor
     * @param color The backgroundcolor to set
     */
    void setBackgroundColor(QColor color);

    /**
     * @brief Returns the backgroundcolor of the screen
     * @return The backgroundColor of the screen
     */
    QColor getBackgroundColor() const {return _color;}

    /**
     * @brief Sets the backgroundimage
     * @param background The backgroundImage
     */
    void setBackgroundImage(QPixmap background);

    /**
     * @brief Returns the backgroundimage
     * @return The backgroundimage of the screen
     */
    QPixmap getBackgroundImage() const {return _image;}

    /**
     * @brief Returns if the image should be used as background
     * @return True if the image should be used as background
     */
    bool useImage() const { return _useImage; }

    /**
     * @brief Returns the center of the screen
     * @return The center of the screen
     */
    QPoint getCenter() const { return QPoint(_size.width()/2, _size.height()/2); }

signals:

    /**
     * @brief Signal is sent when the background updates
     */
    void updated();

public slots:

private:
    QSize _size;
    QColor _color;
    QPixmap _image;
    bool _useImage;

    /**
     * @brief This function is called when the screen changes
     */
    void setChanged() {emit updated();}
};

#endif // SCREENREPR_H
