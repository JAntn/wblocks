#include "FW/UI/ui_record_context_menu.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_explorer.h"
#include <QMenu>
#include <QModelIndexList>
#include <QTableView>

C_UiRecordContextMenu::C_UiRecordContextMenu( C_Controller& controller, const QPoint& global_point, QObject* parent ):
    QObject( parent ), m_Controller( &controller )
{
    QMenu menu;
    bool has_selection = Controller().MainWindow().RecordExplorer().HasSelection();
    long action_flags = Controller().Document().Context().Records().Flags();

    if( ( action_flags & FLAG_ACTION_COPY ) && has_selection )
    {
        QAction* action_copy = menu.addAction( tr( "Copy" ) );
        connect( action_copy, QAction::triggered, &Controller(), C_Controller::OnActionCopyRecord );

    }

    if( ( action_flags & FLAG_ACTION_CUT ) && has_selection )
    {
        QAction* action_copy = menu.addAction( tr( "Cut" ) );
        connect( action_copy, QAction::triggered, &Controller(), C_Controller::OnActionCutRecord );
    }

    if( ( action_flags & FLAG_ACTION_PASTE ) && !Controller().Clipboard().Empty() )
    {
        QAction* action_paste = menu.addAction( tr( "Paste" ) );
        connect( action_paste, QAction::triggered, &Controller(), C_Controller::OnActionPasteRecord );
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( ( action_flags & FLAG_ACTION_OPEN ) && has_selection )
    {
        QAction* action_openrecord = menu.addAction( tr( "Open.." ) );
        connect( action_openrecord, QAction::triggered, &Controller(), C_Controller::OnActionOpenRecordInEditor );
    }

    if( ( action_flags & FLAG_ACTION_PROPERTIES ) && has_selection )
    {
        QAction* action_1 = menu.addAction( tr( "Properties.." ) );
        connect( action_1, QAction::triggered, &Controller(), C_Controller::OnActionChangePropertyWidget );
    }

    if( ( action_flags & FLAG_ACTION_ADD_SCENE ) && has_selection )
    {
        QAction* action_3 = menu.addAction( tr( "Add to scene" ) );
        connect( action_3, QAction::triggered, &Controller(), C_Controller::OnActionAddSceneItem );
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( action_flags & FLAG_ACTION_ADD )
    {
        QAction* action_2 = menu.addAction( tr( "Add" ) );
        connect( action_2, QAction::triggered, &Controller(), C_Controller::OnActionAddRecord );
    }

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection )
    {
        QAction* action_4 = menu.addAction( tr( "Remove" ) );
        connect( action_4, QAction::triggered, &Controller(), C_Controller::OnActionRemoveRecord );
    }

    if( !menu.isEmpty() )
        menu.exec( global_point );
}

C_UiRecordContextMenu::~C_UiRecordContextMenu()
{
    // void
}

