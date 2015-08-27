#ifndef SPRITESWIDGET_H
#define SPRITESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

#include "workspacewidget.h"
#include "../easyblocksmodel.h"

/**
 * @brief The SpritesWidget class
 *
 * @author Brent Chesny
 */
class SpritesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpritesWidget(EasyBlocksModel* model, WorkspaceWidget* wsw, QWidget *parent = 0);

signals:

public slots:
    void showContextMenu(const QPoint &pos);
    void addSpriteFromFileAction();
    void deleteSpriteAction();
    void duplicateSpriteAction();
    void editImagesAction();
    void moveUpAction();
    void moveDownAction();
    void update();
    void drawSprites();
    void selectSprite(QListWidgetItem* qListWidgetItem);

private:
    WorkspaceWidget* _workspace;
    EasyBlocksModel* _model;
    QVBoxLayout* _layout;
    QHBoxLayout* _btnLayout;
    QListWidget* _listWidget;

    void init();
    void createSpritesList();
    void createButtons();
    int getSelectedIndex();
};

#endif // SPRITESWIDGET_H
