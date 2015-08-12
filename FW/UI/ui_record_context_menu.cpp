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
    long position,
    QObject* parent ):
    QObject( parent ),
    m_Document( &document )
{
    QMenu menu;

    list<C_Record*> selection_list = Document()
                                     .MainWindow()
                                     .RecordStructView()
                                     .Selection();

    if( document.Context().Records().Flags() & FLAG_ACTION_COPY )
    {
        if( !selection_list.empty() )
        {
            QAction* action_copy = menu.addAction( tr( "Copy" ) );
            connect( action_copy, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionCopy() ) );
        }
    }

    if( document.Context().Records().Flags() & FLAG_ACTION_CUT )
    {
        if( !selection_list.empty() )
        {
            QAction* action_copy = menu.addAction( tr( "Cut" ) );
            connect( action_copy, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionCut() ) );
        }
    }

    if( document.Context().Records().Flags() & FLAG_ACTION_PASTE )
    {
        if( !document.Clipboard().CopyList().empty() )
        {
            document.Signals().EventData().clear();
            document.Signals().EventData() << QString::number(position);

            QAction* action_paste = menu.addAction( tr( "Paste" ) );
            connect( action_paste, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionPaste() ) );
        }
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( document.Context().Records().Flags() & FLAG_ACTION_EDIT )
    {
        if( position >= 0)
        {
            document.Signals().EventData().clear();
            document.Signals().EventData() << QString::number(position);

            QAction* action_1 = menu.addAction( tr( "Edit" ) );
            connect( action_1, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionEdit() ) );
        }
    }

    if( document.Context().Records().Flags() & FLAG_ACTION_ADD_SCENE )
    {
        if( !selection_list.empty() )
        {
            QAction* action_3 = menu.addAction( tr( "Add to scene" ) );
            connect( action_3, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionAddSceneItem() ) );
        }
    }

    if( !menu.isEmpty() )
        menu.addSeparator();

    if( document.Context().Records().Flags() & FLAG_ACTION_ADD )
    {
        document.Signals().EventData().clear();
        document.Signals().EventData() << QString::number(position);

        QAction* action_2 = menu.addAction( tr( "Add" ) );
        connect( action_2, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionAdd() ) );
    }

    if( document.Context().Records().Flags() & FLAG_ACTION_REMOVE )
    {
        if( !selection_list.empty() )
        {
            QAction* action_4 = menu.addAction( tr( "Remove" ) );
            connect( action_4, SIGNAL( triggered() ), &document.Signals(), SLOT( OnActionRemove() ) );
        }
    }

    if( !menu.isEmpty() )
        menu.exec( global_point );
}

C_UiRecordContextMenu::~C_UiRecordContextMenu()
{
    //void
}

