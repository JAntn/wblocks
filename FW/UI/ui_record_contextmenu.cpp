#include "FW/UI/ui_record_contextmenu.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_explorer.h"
#include <QMenu>
#include <QModelIndexList>
#include <QTableView>

TypeUiRecordContextMenu::TypeUiRecordContextMenu( TypeController& controller, long action_flags, bool has_selection, const QPoint& global_point, QObject* parent ):
    QObject( parent ), TypeVariant( 0 ), m_Controller( &controller )
{

    QMenu menu;

    if( ( action_flags & FLAG_ACTION_COPY ) && has_selection   )
    {
        QAction* action_copy = menu.addAction( tr( "Copy" ) );
        connect( action_copy, QAction::triggered, &Controller(), TypeController::OnActionCopyRecord );
    }

    if( ( action_flags & FLAG_ACTION_CUT ) && has_selection  )
    {
        QAction* action_copy = menu.addAction( tr( "Cut" ) );
        connect( action_copy, QAction::triggered, &Controller(), TypeController::OnActionCutRecord );
    }

    if( ( action_flags & FLAG_ACTION_PASTE )  && ( !controller.Clipboard().Empty() ) )
    {
        QAction* action_paste = menu.addAction( tr( "Paste" ) );
        connect( action_paste, QAction::triggered, &Controller(), TypeController::OnActionPasteRecord );
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( ( action_flags & FLAG_ACTION_OPEN ) && has_selection  )
    {
        QAction* action_openrecord = menu.addAction( tr( "Open" ) );
        connect( action_openrecord, QAction::triggered, &Controller(), TypeController::OnActionOpenRecordInEditor );
    }

    if( ( action_flags & FLAG_ACTION_ADD_SCENE ) && has_selection  )
    {
        QAction* action_3 = menu.addAction( tr( "Add to scene" ) );
        connect( action_3, QAction::triggered, &Controller(), TypeController::OnActionAddSceneItem );
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( action_flags & FLAG_ACTION_ADD )
    {
        QAction* action_2 = menu.addAction( tr( "Add" ) );
        connect( action_2, QAction::triggered, &Controller(), TypeController::OnActionAddRecord );
    }

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection  )
    {
        QAction* action_4 = menu.addAction( tr( "Remove" ) );
        connect( action_4, QAction::triggered, &Controller(), TypeController::OnActionRemoveRecord );
    }

    if( !menu.isEmpty() )
        menu.exec( global_point );
}

TypeUiRecordContextMenu::~TypeUiRecordContextMenu()
{
    // void
}

