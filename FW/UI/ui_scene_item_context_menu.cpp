#include "FW/UI/ui_scene_item_context_menu.h"
#include "FW/SC/scene.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QMessageBox>

C_UiSceneItemContextMenu::C_UiSceneItemContextMenu(
    C_SceneItem& item,
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

C_UiSceneItemContextMenu::~C_UiSceneItemContextMenu()
{
    //void
}

void C_UiSceneItemContextMenu::OnEditRecordProperties()
{
    SceneItem()
    .Record()
    .PropertyWidget(
        SceneItem()
        .Scene()
        .Document().Controller() );
}

void C_UiSceneItemContextMenu::OnRemove()
{
    if( C_Controller::AcceptMessage(
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

void C_UiSceneItemContextMenu::OnRemoveFromScene()
{
    if( C_Controller::AcceptMessage(
                tr( "Remove this item from scene?" ) ) )
        delete & SceneItem();
}

