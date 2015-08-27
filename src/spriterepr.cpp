#include "spriterepr.h"

#include "blockrepr.h"

#include <QDebug>
#include <QBuffer>

SpriteRepr::SpriteRepr(QPixmap* image, QString name, QPoint pos) :  _name(name), _rotation(0), _selectedImage(0)
{
    appendImage(image);
    _position = pos;

    if (image != NULL)
        _size = QSize(image->size());
}

SpriteRepr::SpriteRepr(const SpriteRepr &sprite) : BlockReprHolder(sprite)
{
    _name = sprite.getName();
    foreach (VarBlockRepr* var, sprite.getVars()) {
        _vars.append((VarBlockRepr*) var->copy());
    }
    foreach (QPixmap* image, sprite.getImages()) {
        _images.append(new QPixmap(*image));
    }
    _size = sprite.getSize();
    _position = sprite.getPosition();
    _rotation = sprite.getRotation();
    _selectedImage = sprite.getSelectedImageIndex();
}

SpriteRepr::~SpriteRepr()
{
    qDeleteAll(_images);
    qDeleteAll(_vars);
}

void SpriteRepr::addImage(QPixmap* image, int index)
{
    if(image != NULL) {
        _images.insert(index, image);
        emit graphicsUpdated();
    }
}

void SpriteRepr::appendImage(QPixmap* image)
{
    if(image != NULL) {
        _images.append(image);
        emit graphicsUpdated();
    }
}

bool SpriteRepr::removeImage(QPixmap* image)
{
    //ignore if only one image left
    if(_images.size() <= 1)
        return false;

    for(int i = 0; i < _images.size(); i++) {
        if(_images[i] == image) {
            _images.removeAt(i);
            if(_selectedImage >= i)
                _selectedImage--;
            emit graphicsUpdated();
            return true;
        }
    }

    return false;
}

bool SpriteRepr::removeImage(int index)
{
    //ignore if only one image left
    if(_images.size() <= 1)
        return false;

    if(index >= 0 && index < _images.size()) {
        _images.removeAt(index);
        if(_selectedImage >= index)
            _selectedImage--;
        emit graphicsUpdated();
        return true;
    }

    return false;
}

void SpriteRepr::setImages(QList<QPixmap *> images)
{
    //don't allow empty list
    if(images.size() == 0)
        return;

    _images = images;
    emit graphicsUpdated();
}

void SpriteRepr::setSelectedImage(int selected)
{
    _selectedImage = selected;

    if(_selectedImage < 0 || _selectedImage >= _images.size())
        _selectedImage = 0;

    emit graphicsUpdated();
}

void SpriteRepr::addVariable(VarBlockRepr* var)
{
    _vars.append(var);
    emit blocksUpdated();
}

void SpriteRepr::removeVariable(VarBlockRepr *var)
{
    _vars.removeAll(var);
}

bool SpriteRepr::hasVariableWithName(QString name)
{
    foreach(VarBlockRepr* var, _vars)
    {
        if (var->getVarName() == name)
            return true;
    }

    return false;
}


