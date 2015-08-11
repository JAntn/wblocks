#include "FW/UI/ui_record_context_menu.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"

#include "FW/UI/ui_add_record.h"

#include <QMenu>

C_UiRecordContextMenu::C_UiRecordContextMenu(
    C_Document& document,
    const QPoint& global_point,
    long position,
    C_Record* record,
    QObject* parent ):
    QObject( parent ),
    m_Record( record ),
    m_Document( &document ),
    m_Position( position )
{
    QMenu menu;

    if( m_Record != 0 )
    {
        if( document.Context().Records().Flags() & FLAG_ACTION_COPY & Record().Flags() )
        {
            QAction* action_copy = menu.addAction( tr( "Copy" ) );
            connect( action_copy, SIGNAL( triggered() ), this, SLOT( OnCopy() ) );
        }

        if( document.Context().Records().Flags() & FLAG_ACTION_PASTE )
        {
            if( !document.Clipboard().IdList().isEmpty() )
            {
                QAction* action_paste = menu.addAction( tr( "Paste" ) );
                connect( action_paste, SIGNAL( triggered() ), this, SLOT( OnPaste() ) );
            }
        }

        if( !menu.isEmpty() )
            menu.addSeparator();

        if( document.Context().Records().Flags() & FLAG_ACTION_EDIT & Record().Flags() )
        {
            QAction* action_1 = menu.addAction( tr( "Edit" ) );
            connect( action_1, SIGNAL( triggered() ), this, SLOT( OnEdit() ) );
        }

        if( document.Context().Records().Flags() & FLAG_ACTION_ADD )
        {
            QAction* action_2 = menu.addAction( tr( "Add" ) );
            connect( action_2, SIGNAL( triggered() ), this, SLOT( OnAdd() ) );
        }

        if( document.Context().Records().Flags() & FLAG_ACTION_ADD_SCENE & Record().Flags() )
        {
            QAction* action_3 = menu.addAction( tr( "Add to scene" ) );
            connect( action_3, SIGNAL( triggered() ), this, SLOT( OnAddSceneItem() ) );
        }

        if( !menu.isEmpty() )
            menu.addSeparator();

        if( document.Context().Records().Flags() & FLAG_ACTION_REMOVE & Record().Flags() )
        {
            QAction* action_4 = menu.addAction( tr( "Remove" ) );
            connect( action_4, SIGNAL( triggered() ), this, SLOT( OnRemove() ) );
        }
    }
    else
    {
        if( document.Context().Records().Flags() & FLAG_ACTION_PASTE )
        {
            if( !document.Clipboard().IdList().isEmpty() )
            {
                QAction* action_paste = menu.addAction( tr( "Paste" ) );
                connect( action_paste, SIGNAL( triggered() ), this, SLOT( OnPaste() ) );
            }
        }

        if( document.Context().Records().Flags() & FLAG_ACTION_ADD )
        {
            QAction* action_5 = menu.addAction( tr( "Add" ) );
            connect( action_5, SIGNAL( triggered() ), this, SLOT( OnAdd() ) );
        }
    }

    if( !menu.isEmpty() )
        menu.exec( global_point );
}

C_UiRecordContextMenu::~C_UiRecordContextMenu()
{
    //void
}


void C_UiRecordContextMenu::OnEdit()
{
    Record().ShowEditor( Document() );
}

void C_UiRecordContextMenu::OnRemove()
{
    if( C_Document::AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();

        emit Document()
        .Signals()
        .RecordsChanged();
    }
}

void C_UiRecordContextMenu::OnAdd()
{
    QWidget* dialog;

    if( m_Record != 0 )
    {
        dialog = new C_UiAddRecord(
            Document(),
            Document()
            .Context()
            .Records()
            .GetIndex( &Record() ) );
    }
    else
        dialog = new C_UiAddRecord( Document() );

    dialog->show();
}

void C_UiRecordContextMenu::OnAddSceneItem()
{
    Document()
    .Context()
    .Scene()
    .CreateItem( Record() );

    emit Document()
    .Signals()
    .SceneChanged();
}

void C_UiRecordContextMenu::OnCopy()
{
    if( m_Record != 0 )
    {
        QStringList id_list;
        id_list << Record().Id();

        Document()
        .Clipboard()
        .Copy(
            Document().Context().Records(),
            id_list
        );
    }
}

void C_UiRecordContextMenu::OnPaste()
{
    Document()
    .Clipboard()
    .Paste(
        Document().Context().Records(),
        Position()
    );

    emit Document().Signals().RecordsChanged();
}


