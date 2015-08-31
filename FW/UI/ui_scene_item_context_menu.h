#ifndef TypeSCENE_ITEM_CONTEXT_MENU_H
#define TypeSCENE_ITEM_CONTEXT_MENU_H

#include "FW/macro.h"

#include <QGraphicsSceneMouseEvent>
#include <QObject>

class TypeSceneItem;

class TypeUiSceneItemContextMenu : public QObject
{
    Q_OBJECT

public:

    TypeUiSceneItemContextMenu( TypeSceneItem& item,
                              QGraphicsSceneContextMenuEvent* event,
                              QObject* parent = 0 );

    ~TypeUiSceneItemContextMenu() override;

    M_POINTER           ( SceneItem, TypeSceneItem )

public slots:

    void                OnEditRecordProperties();
    void                OnRemove();
    void                OnRemoveFromScene();

};

#endif // TypeSCENE_ITEM_CONTEXT_MENU_H
