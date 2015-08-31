#include "FW/UI/ui_scene_item_context_menu.h"
#include "FW/SC/scene.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QMessageBox>

TypeUiSceneItemContextMenu::TypeUiSceneItemContextMenu(
    TypeSceneItem& item,
    QGraphicsSceneContextMenuEvent* event,
    QObject* parent ):
    QObject( parent ),
    m_SceneItem( &item )
{
    QMenu menu;

    if( FLAG_ACTION_PROPERTIES & SceneItem().Record().Flags() )
    {
        QAction* action1 = menu.addAction( tr( "Properties" ) );
        connect( action1, SIGNAL( triggered() ), this, SLOT( OnEditRecordProperties() ) );
    }

    menu.addSeparator();

    if( FLAG_ACTION_REMOVE_SCENE & SceneItem().Record().Flags() )
    {
        QAction* action2 = menu.addAction( tr( "Remove from scene" ) );
        connect( action2, SIGNAL( triggered() ), this, SLOT( OnRemoveFromScene() ) );
    }

    if( FLAG_ACTION_REMOVE & SceneItem().Record().Flags() )
    {
        QAction* action3 = menu.addAction( tr( "Remove from document" ) );
        connect( action3, SIGNAL( triggered() ), this, SLOT( OnRemove() ) );
    }

    menu.exec( event->screenPos() );
}

TypeUiSceneItemContextMenu::~TypeUiSceneItemContextMenu()
{
    //void
}

void TypeUiSceneItemContextMenu::OnEditRecordProperties()
{
    SceneItem()
    .Record()
    .PropertyWidget(
        SceneItem()
        .Scene()
        .Document().Controller() );
}

void TypeUiSceneItemContextMenu::OnRemove()
{
    if( TypeController::AcceptMessage(
                tr( "Remove this record?" ) ) )
    {
        delete & SceneItem().Record();
        emit SceneItem()
        .Scene()
        .Document()
        .Controller()
        .RecordsChanged();
    }
}

void TypeUiSceneItemContextMenu::OnRemoveFromScene()
{
    if( TypeController::AcceptMessage(
                tr( "Remove this item from scene?" ) ) )
        delete & SceneItem();
}

