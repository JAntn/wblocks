#ifndef C_SCENE_ITEM_CONTEXT_MENU_H
#define C_SCENE_ITEM_CONTEXT_MENU_H

#include "FW/macro.h"

#include <QGraphicsSceneMouseEvent>
#include <QObject>

class C_SceneItem;

class C_UiSceneItemContextMenu : public QObject
{
    Q_OBJECT

public:

                        C_UiSceneItemContextMenu(C_SceneItem& item,
                                               QGraphicsSceneContextMenuEvent *event,
                                               QObject* parent =0);

                        ~C_UiSceneItemContextMenu() override;

    C_POINTER           (SceneItem, C_SceneItem)

public slots:

    void                OnEdit();
    void                OnRemove();
    void                OnRemoveFromScene();

};

#endif // C_SCENE_ITEM_CONTEXT_MENU_H
