#ifndef SPRITEREPR_H
#define SPRITEREPR_H

#include <QList>
#include <QPixmap>

#include "blockreprholder.h"
#include "blockrepr/varblockrepr.h"

class BlockRepr;
class Project;

/**
 * @brief The SpriteRepr class
 *
 * @author Brecht Vandevoort
 */
class SpriteRepr : public BlockReprHolder
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     */
    SpriteRepr(QPixmap* image = NULL, QString name = QString(), QPoint pos = QPoint(0, 0));

    /**
     * @brief Copy constructor
     * @param sprite The sprite to copy
     */
    SpriteRepr(const SpriteRepr &sprite);

    /**
     * @brief Destructor
     */
    ~SpriteRepr();

    /**
     * @brief Adds an image to the sprite
     * @param image The image to add
     * @param index Index of the image in this sprite, default is in front
     */
    void addImage(QPixmap* image, int index = 0);

    /**
     * @brief Adds an image to the sprite at the end of the list of sprites
     * @param image The image to add
     */
    void appendImage(QPixmap* image);

    /**
     * @brief Removes an image from the sprite
     * @param image The image to remove
     * @return true if the image was deleted, false if not
     */
    bool removeImage(QPixmap* image);

    /**
     * @brief Removes an image from this sprite
     * @param index Index of the image to remove
     * @return True if the image was deleted, false if not
     */
    bool removeImage(int index);

    /**
     * @brief Sets the list of images for this sprite
     * @param images The list of images
     */
    void setImages(QList<QPixmap*> images);

    /**
     * @brief Returns a list of images
     * @return The list of images in this sprite
     */
    QList<QPixmap*> getImages() const {return _images;}

    /**
     * @brief Sets the position of this sprite
     * @param position The position to set this sprite to
     */
    void setPosition(QPoint position) {_position = position; emit graphicsUpdated();}

    /**
     * @brief Returns the position of the sprite
     * @return The position of the sprite
     */
    QPoint getPosition() const {return _position;}

    /**
     * @brief Sets the size of this sprite
     * @param size The size to set
     */
    void setSize(QSize size) {_size = size; emit graphicsUpdated();}

    /**
     * @brief Returns the size of this sprite
     * @return The size of the sprite
     */
    QSize getSize() const {return _size;}

    /**
     * @brief Sets the rotation of this sprite
     * @param rotation The rotation to set
     */
    void setRotation(int rotation) {_rotation = rotation%360; emit graphicsUpdated();}

    /**
     * @brief Returns the rotation of this sprite
     * @return The rotation of this sprite
     */
    int getRotation() const {return _rotation;}

    /**
     * @brief Returns the name of the sprite
     * @return The name of the sprite
     */
    QString getName() const { return _name; }

    /**
     * @brief Setter for the name of the sprite
     * @param name The name of the sprite
     */
    void setName(QString name) { _name = name; emit nameChanged(); emit graphicsUpdated();}

    /**
     * @brief Returns the currently selected image
     * @return  The currently Selected image
     */
    QPixmap getCurrentImage() const {return *_images.at(_selectedImage);}

    /**
     * @brief Returns the index of the currently selected images
     * @return The index of the currently selected image
     */
    int getSelectedImageIndex() const {return _selectedImage;}

    /**
     * @brief Sets the selected image
     * @param selected Index of the image to select
     */
    void setSelectedImage(int selected);

    /**
     * @brief Adds a variable to the sprite
     * @param var The var to add
     */
    void addVariable(VarBlockRepr* var);

    /**
     * @brief Removes a variable from the sprite
     * @param var The variable to remove
     */
    void removeVariable(VarBlockRepr* var);

    /**
     * @brief Checks if a var with the name already exists
     * @param name Name of the var
     * @return True if it already exists
     */
    bool hasVariableWithName(QString name);

    /**
     * @brief Returns a list containing the different vars of this sprite
     * @return List containing the vars of this sprite
     */
    QList<VarBlockRepr*> getVars() const { return _vars; }

signals:
    /**
     * @brief Signal is sent every time the sprite graphically changes
     */
    void graphicsUpdated();

    /**
     * @brief Signal is sent every time the sprite's name changes
     */
    void nameChanged();

private:
    QString _name;
    QList<VarBlockRepr*> _vars;
    QList<QPixmap*> _images;
    QPoint _position;
    QSize _size;
    int _rotation;
    int _selectedImage;

};

#endif // SPRITEREPR_H
