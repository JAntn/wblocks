#include "FW/UI/ui_record_context_menu.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_main_window.h"
#include <QMenu>
#include <QModelIndexList>
#include <QTableView>
#include "FW/UI/ui_record_struct_view.h"

C_UiRecordContextMenu::C_UiRecordContextMenu(
    C_Document& document,
    const QPoint& global_point,
    QObject* parent ):
    QObject( parent ),
    m_Document( &document )
{
    QMenu menu;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    long action_flags = document
                 .Context()
                 .Records()
                 .Flags();

    if( ( action_flags & FLAG_ACTION_COPY ) && has_selection )
    {
        QAction* action_copy = menu.addAction( tr( "Copy" ) );
        connect( action_copy, QAction::triggered, &document.Events(), C_Events::OnActionCopy );

    }

    if( ( action_flags & FLAG_ACTION_CUT ) && has_selection )
    {

        QAction* action_copy = menu.addAction( tr( "Cut" ) );
        connect( action_copy, QAction::triggered, &document.Events(), C_Events::OnActionCut );
    }

    if( ( action_flags & FLAG_ACTION_PASTE ) && !document.Clipboard().Empty() )
    {
        QAction* action_paste = menu.addAction( tr( "Paste" ) );
        connect( action_paste, QAction::triggered, &document.Events(), C_Events::OnActionPaste );
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( ( action_flags & FLAG_ACTION_EDIT ) && has_selection )
    {
        QAction* action_1 = menu.addAction( tr( "Edit" ) );
        connect( action_1, QAction::triggered, &document.Events(), C_Events::OnActionEdit );
    }

    if( ( action_flags & FLAG_ACTION_ADD_SCENE ) && has_selection )
    {
        QAction* action_3 = menu.addAction( tr( "Add to scene" ) );
        connect( action_3, QAction::triggered, &document.Events(), C_Events::OnActionAddSceneItem );
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( action_flags & FLAG_ACTION_ADD )
    {
        QAction* action_2 = menu.addAction( tr( "Add" ) );
        connect( action_2, QAction::triggered, &document.Events(), C_Events::OnActionAdd );
    }

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection )
    {
        QAction* action_4 = menu.addAction( tr( "Remove" ) );
        connect( action_4, QAction::triggered, &document.Events(), C_Events::OnActionRemove );
    }

    if( !menu.isEmpty() )
        menu.exec( global_point );
}

C_UiRecordContextMenu::~C_UiRecordContextMenu()
{
    //void
}

