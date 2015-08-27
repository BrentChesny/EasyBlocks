#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>

#include "simplevartable.h"
#include "spritevartable.h"
#include "eventblock.h"

class ProgramModel;

/**
 * @brief The Sprite class
 *
 * @author Brent Chesny
 */
class Sprite
{
public:
    /**
     * @brief Constructor method
     * @param globalVars The global variable table
     */
    Sprite(SimpleVarTable* globalVars, QPixmap* image, ProgramModel* programModel);

    /**
     * @brief Destructor method
     */
    ~Sprite();

    /**
     * @brief Returns the programModel
     * @return A pointer to the programModel
     */
    ProgramModel* getProgramModel() const {return _programModel;}

    /**
     * @brief Adds an event block to the list of event block of this sprite
     * @param block The block to add
     */
    void addBlock(EventBlock* block) { _blocks.append(block); }

    /**
     * @brief Adds an image to the imagelist
     * @param image The image to add to the imagelist
     */
    void addImage(QPixmap* image) { _images.append(image); }

    /**
     * @brief Sends a signal to the sprite
     * @param signal The signal to send
     */
    void sendSignal(const Signal &signal);

    /**
     * @brief Sets the next image for the sprite
     */
    void nextImage();

    /**
     * @brief Sets the selected image
     * @param index The index
     */
    void setSelectedImage(int index);

    /**
     * @brief Sets the size for the sprite
     * @param size The size
     */
    void setSize(QSize size) { _size = size; }

    /**
     * @brief Getter for the size
     * @return The size
     */
    QSize getSize() const { return _size; }

    /**
     * @brief Sets the rotation for the sprite
     * @param rotation The rotation
     */
    void setRotation(int rotation) { _rotation = rotation; }

    /**
     * @brief Getter for the rotation property
     * @return The rotation value of the sprite
     */
    int getRotation() const { return _rotation; }

    /**
     * @brief Getter for the vartable of the sprite
     * @return The vartable of the sprite
     */
    SpriteVarTable* getVarTable() const { return _vars; }

    /**
     * @brief Getter for the current image of the sprite
     * @return The current image of the sprite
     */
    QPixmap* getCurrentImage() const { return _images.at(_selectedImage); }

    /**
     * @brief Getter for the position of the sprite
     * @return The position of the sprite
     */
    QPoint getPosition() const { return _position; }

    /**
     * @brief Setter for the position of the sprite
     * @param pos The new position of the sprite
     */
    void setPosition(QPoint pos) { _position = pos; }

    /**
     * @brief Setter for the visibility of the sprite
     * @param visible If true, the sprite is visible
     */
    void setVisible(bool visible) {_isVisible = visible;}

    /**
     * @brief Setter for the visibility of the sprite
     * @return True if the sprite is visible, false if not
     */
    bool getVisible() const {return _isVisible;}

private:
    SpriteVarTable* _vars;

    ProgramModel* _programModel;

    QList<EventBlock*> _blocks;

    QList<QPixmap*> _images;

    int _selectedImage;

    QSize _size;

    QPoint _position;

    int _rotation;

    bool _isVisible;
};

#endif // SPRITE_H
