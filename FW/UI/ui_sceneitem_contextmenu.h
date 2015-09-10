#ifndef SCENE_ITEM_CONTEXT_MENU_H
#define SCENE_ITEM_CONTEXT_MENU_H

#include "FW/tools.h"
#include <QGraphicsSceneMouseEvent>

class TypeSceneItem;
class TypeController;

class TypeUiSceneItemContextMenu : public QObject
{
    Q_OBJECT

public:

    TypeUiSceneItemContextMenu( TypeController& controller, TypeSceneItem& item,
                              QGraphicsSceneContextMenuEvent* event,
                              QObject* parent = 0 );

    ~TypeUiSceneItemContextMenu() override;

    M_REFERENCE         ( SceneItem, TypeSceneItem )
    M_REFERENCE         ( Controller, TypeController )

public slots:

    void                OnActionChangePropertyWidget();
    void                OnActionRemoveRecord();
    void                OnActionRemoveSceneItem();
    void                OnActionOpenRecordInEditor();

};

#endif // SCENE_ITEM_CONTEXT_MENU_H
