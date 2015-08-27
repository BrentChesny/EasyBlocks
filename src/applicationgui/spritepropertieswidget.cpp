#include "spritepropertieswidget.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>

SpritePropertiesWidget::SpritePropertiesWidget(EasyBlocksModel* model, QWidget *parent) :
    QWidget(parent), _model(model), _nameProperty(NULL), _posProperty(NULL), _sizeProperty(NULL), _rotationProperty(NULL)
{
    init();
    connect(_model, SIGNAL(updated()), this, SLOT(updateValues()));
}

void SpritePropertiesWidget::init()
{
    _layout = new QVBoxLayout;
    _layout->setAlignment(Qt::AlignTop);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);
    setLayout(_layout);

    // create label
    QLabel* spritesLabel = new QLabel(tr("Properties"));
    spritesLabel->setAlignment(Qt::AlignLeft);
    QFont font("Arial", 12, QFont::DemiBold);
    font.setPixelSize(12);
    spritesLabel->setFont(font);
    spritesLabel->setContentsMargins(0, 0, 0, 9);
    _layout->addWidget(spritesLabel);

    createPropertyBrowser();
}

void SpritePropertiesWidget::createPropertyBrowser()
{
    SpriteRepr* sprite = _model->getProject()->getCurrentSprite();

    QtVariantPropertyManager *variantManager = new QtVariantPropertyManager(this);
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    QtTreePropertyBrowser *variantEditor = new QtTreePropertyBrowser();

    _layout->addWidget(variantEditor);
    connect(variantManager, SIGNAL(valueChanged(QtProperty*,QVariant)), this, SLOT(valueChanged(QtProperty*,QVariant)));

    _nameProperty = variantManager->addProperty(QVariant::String, tr("Sprite Name"));
    _nameProperty->setValue(sprite->getName());
    variantEditor->addProperty(_nameProperty);

    _posProperty = variantManager->addProperty(QVariant::Point, tr("Position"));
    _posProperty->setValue(sprite->getPosition());
    variantEditor->addProperty(_posProperty);

    _sizeProperty = variantManager->addProperty(QVariant::Size, tr("Size"));
    _sizeProperty->setValue(sprite->getSize());
    variantEditor->addProperty(_sizeProperty);

    _rotationProperty = variantManager->addProperty(QVariant::Int, tr("Rotation"));
    _rotationProperty->setValue(sprite->getRotation());
    variantEditor->addProperty(_rotationProperty);

    variantEditor->setFactoryForManager(variantManager, variantFactory);
    variantEditor->setPropertiesWithoutValueMarked(true);
    variantEditor->setRootIsDecorated(false);
    variantEditor->setFocusPolicy(Qt::NoFocus);
}

void SpritePropertiesWidget::updateValues()
{
    SpriteRepr* sprite = _model->getProject()->getCurrentSprite();
    if (sprite == NULL) {
        _nameProperty->setValue(QString());
        _posProperty->setValue(QPoint());
        _sizeProperty->setValue(QSize());
        _rotationProperty->setValue(0);
        return;
    }

    _nameProperty->setValue(sprite->getName());
    _posProperty->setValue(sprite->getPosition());
    _sizeProperty->setValue(sprite->getSize());
    _rotationProperty->setValue(sprite->getRotation());
}

void SpritePropertiesWidget::valueChanged(QtProperty* property, QVariant value)
{
    SpriteRepr* sprite = _model->getProject()->getCurrentSprite();
    if (sprite == NULL)
        return;

    if (property == _nameProperty)
        sprite->setName(value.toString());
    else if (property == _posProperty)
        sprite->setPosition(value.toPoint());
    else if (property == _sizeProperty)
        sprite->setSize(value.toSize());
    else if (property == _rotationProperty)
        sprite->setRotation(value.toInt());
}
