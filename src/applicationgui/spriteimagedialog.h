#ifndef SPRITEIMAGEDIALOG_H
#define SPRITEIMAGEDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class SpriteImageDialog;
}

class SpriteImageDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param images The current list of images of the sprite
     * @param parent The QWidget parent
     */
    explicit SpriteImageDialog(QList<QPixmap*> images, QWidget *parent = 0);
    ~SpriteImageDialog();

    /**
     * @brief Returns the edited list of images
     * @return The edited list of images
     */
    QList<QPixmap*> getImages() const { return _images; }

    /**
     * @brief Returns the selected image
     * @return The selected image
     */
    int getSelected() const { return _current; }

public slots:
    void addImage();
    void removeImage();
    void rowSelectionChanged(int index);

private:
    Ui::SpriteImageDialog *ui;

    QList<QPixmap*> _images;
    QGraphicsScene* _scene;

    void fillList();
    void drawPreview();
    void update();

    int _current;
};

#endif // SPRITEIMAGEDIALOG_H
