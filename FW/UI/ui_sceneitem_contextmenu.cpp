#include "FW/UI/ui_sceneitem_contextmenu.h"
#include "FW/SC/scene.h"
#include "FW/RC/record.h"
#include "FW/controller.h"
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QMessageBox>

TypeUiSceneItemContextMenu::TypeUiSceneItemContextMenu(
    TypeController& controller,
    TypeSceneItem& item,
    QGraphicsSceneContextMenuEvent* event,
    QObject* parent ):
    QObject( parent ),
    m_SceneItem( &item ),
    m_Controller( &controller )
{
    QMenu menu;

    long action_flags = item.Record().ParentStruct()->Flags();

    if( action_flags & FLAG_ACTION_OPEN )
    {
        QAction* action_openrecord = menu.addAction( tr( "Open.." ) );
        connect( action_openrecord, QAction::triggered, this, TypeUiSceneItemContextMenu::OnActionOpenRecordInEditor );
    }

    if( action_flags & FLAG_ACTION_ACTIVATE )
    {
        QAction* action1 = menu.addAction( tr( "Properties.." ) );
        connect( action1, QAction::triggered, this, TypeUiSceneItemContextMenu::OnActionChangePropertyWidget );
    }

    menu.addSeparator();

    if( action_flags & FLAG_ACTION_REMOVE_SCENE )
    {
        QAction* action2 = menu.addAction( tr( "Remove from scene" ) );
        connect( action2, QAction::triggered, this, TypeUiSceneItemContextMenu::OnActionRemoveSceneItem );
    }

    if( action_flags & FLAG_ACTION_REMOVE )
    {
        QAction* action3 = menu.addAction( tr( "Remove from document" ) );
        connect( action3, QAction::triggered, this, TypeUiSceneItemContextMenu::OnActionRemoveRecord  );
    }

    menu.exec( event->screenPos() );
}

TypeUiSceneItemContextMenu::~TypeUiSceneItemContextMenu()
{
    // void
}

void TypeUiSceneItemContextMenu::OnActionOpenRecordInEditor()
{
    long action_flags = SceneItem().Record().ParentStruct()->Flags();

    if( action_flags & FLAG_ACTION_OPEN )
    {
        if( !( SceneItem().Record().Flags() & FLAG_ACTION_OPEN ) )
        {
            qDebug() << "FLAG_ACTION_OPEN is disabled on record:"
                     << SceneItem().Record().Name();
            return;
        }

        Controller().OpenRecordEditorWidget( SceneItem().Record() );
    }
    else
    {
        qDebug() << "FLAG_ACTION_OPEN is disabled on parent struct";
        return;
    }
}

void TypeUiSceneItemContextMenu::OnActionChangePropertyWidget()
{
    long action_flags = SceneItem().Record().ParentStruct()->Flags();

    if( action_flags & FLAG_ACTION_ACTIVATE )
    {
        if( !( SceneItem().Record().Flags() & FLAG_ACTION_ACTIVATE ) )
        {
            qDebug() << "FLAG_ACTION_ACTIVATE is disabled on record:"
                     << SceneItem().Record().Name();
            return;
        }

        emit Controller().SetActiveRecord( &SceneItem().Record() );
    }
    else
    {
        qDebug() << "FLAG_ACTION_ACTIVATE is disabled on parent struct";
        return;
    }
}

void TypeUiSceneItemContextMenu::OnActionRemoveRecord()
{
    long action_flags = SceneItem().Record().ParentStruct()->Flags();

    if( action_flags & FLAG_ACTION_REMOVE )
    {
        if( !( SceneItem().Record().Flags() & FLAG_ACTION_REMOVE ) )
        {
            qDebug() << "FLAG_ACTION_REMOVE is disabled on record:"
                     << SceneItem().Record().Name();
            return;
        }

        if( TypeController::AcceptMessage(
                    tr( "Remove this record?" ) ) )
        {
            delete & SceneItem().Record();
            emit Controller().RecordsChanged();
        }
    }
    else
    {
        qDebug() << "FLAG_ACTION_REMOVE is disabled on parent struct";
        return;
    }
}

void TypeUiSceneItemContextMenu::OnActionRemoveSceneItem()
{
    long action_flags = SceneItem().Record().ParentStruct()->Flags();

    if( action_flags & FLAG_ACTION_REMOVE_SCENE )
    {
        if( !( SceneItem().Record().Flags() & FLAG_ACTION_REMOVE_SCENE ) )
        {
            qDebug() << "FLAG_ACTION_REMOVE_SCENE is disabled on record:"
                     << SceneItem().Record().Name();
            return;
        }

        if( TypeController::AcceptMessage(
                    tr( "Remove this item from scene?" ) ) )
            delete & SceneItem();
    }
    else
    {
        qDebug() << "FLAG_ACTION_REMOVE_SCENE is disabled on parent struct";
        return;
    }
}

