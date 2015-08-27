#include "sprite.h"

#include "qalgorithms.h"
#include "programmodel.h"

Sprite::Sprite(SimpleVarTable *globalVars, QPixmap* image, ProgramModel* programModel) : _programModel(programModel), _selectedImage(0), _position(QPoint(0, 0)), _rotation(0), _isVisible(true)
{
    _vars = new SpriteVarTable(globalVars);
    _images.append(image);

    if (image != NULL)
        _size = image->size();
}

Sprite::~Sprite()
{
    qDeleteAll(_images);
    qDeleteAll(_blocks);

    delete _vars;
}

void Sprite::sendSignal(const Signal& signal)
{
    foreach (EventBlock* b, _blocks) {
        b->sendSignal(signal, this);
    }
}

void Sprite::nextImage()
{
    _selectedImage = (_selectedImage + 1) % _images.size();
}

void Sprite::setSelectedImage(int index)
{
    if(index < 0 || index >= _images.size())
        return;
    _selectedImage = index;
}
