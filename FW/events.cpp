#include "FW/document.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_struct_view.h"
#include "FW/UI/ui_add_record.h"
#include <QFileDialog>
#include "FW/RC/record_struct.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include <QList>
#include "ui_mainwindow.h"
#include <FW/UI/ui_find_record.h>
#include <QWebFrame>

C_Events::C_Events( C_Document& document, C_UiMainWindow& main_window, QObject* parent )
    : QObject( parent )
{
    m_Document = &document;
    m_MainWindow = &main_window;
}

C_Events::~C_Events()
{
    // void
}

void C_Events::ConnectEvents()
{
    // TODO : move signals to C_Document
    connect(
        this,
        C_Events::RecordsChanged,
        this,
        C_Events::OnRecordsChanged );

    connect(
        this,
        C_Events::SceneChanged,
        this,
        C_Events::OnSceneChanged );

    connect(
        this,
        C_Events::ScriptChanged,
        this,
        C_Events::OnScriptChanged );
}

void C_Events::OnRecordsChanged()
{
    MainWindow().UpdateTableView();
    Document().UpdateScript();
    Document().UpdateScene();
}

void C_Events::OnScriptChanged()
{
    MainWindow().UpdateScriptView();
}

void C_Events::OnSceneChanged()
{
    MainWindow().UpdateSceneView();
}

void C_Events::OnActionFileLoad()
{
    QString file_name = QFileDialog::getOpenFileName( &MainWindow(),
                        tr( "Load File" ),
                        "",
                        tr( "JS Blocks Files (*.blk)" ) );

    if( file_name.isEmpty() )
        return;

    QFile file( file_name );
    Document().FileLoad( file );

}

void C_Events::OnActionFileSave()
{
    QString file_name = QFileDialog::getSaveFileName( &MainWindow(),
                        tr( "Save File" ),
                        tr( "untitled.blk" ),
                        tr( "JS Blocks Files (*.blk)" ) );

    if( file_name.isEmpty() )
        return;

    QFile file( file_name );
    Document().FileSave( file );
}

void C_Events::OnActionSQLLoad()
{
    QString file_name = QFileDialog::getOpenFileName( &MainWindow(),
                        tr( "Load SQL Database File" ),
                        "",
                        tr( "SQL Files (*.sql)" ) );

    if( file_name.isEmpty() )
        return;

    Document().DatabaseLoad( file_name );
}

void C_Events::OnActionSQLSave()
{
    QString file_name = QFileDialog::getSaveFileName( &MainWindow(),
                        tr( "Save SQL Database File" ),
                        tr( "untitled.sql" ),
                        tr( "SQL Files (*.sql)" ) );

    if( file_name.isEmpty() )
        return;

    Document().DatabaseSave( file_name );
}

void C_Events::OnActionScriptSave()
{
    QString file_name = QFileDialog::getSaveFileName( &Document().MainWindow(),
                        tr( "Save Java Script File" ),
                        tr( "untitled.js" ),
                        tr( "JS Files (*.js)" ) );

    if( file_name.isEmpty() )
        return;

    Document().Script().Generate( Document().Records() );
    emit Document().Events().ScriptChanged();
    C_Document::SaveTextFile( file_name, Document().Script().StringList().join( "" ) );
}

void C_Events::OnActionEdit()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags() ;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection )
    {
        auto record =
            static_cast<C_Record*>(
                *Document()
                .Context()
                .Records()
                .begin()
            );

        record->ShowEditor( Document() );
    }
}

void C_Events::OnActionRemove()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags() ;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection )
    {
        list<C_Record*> selection_list =
            Document()
            .MainWindow()
            .RecordStructView()
            .Selection();

        if( selection_list.size() == 1 )
        {
            if( !C_Document::AcceptMessage( tr( "Do you want to remove this record?" ) ) )
                return;
        }
        else
        {
            if( !C_Document::AcceptMessage( tr( "Do you want to remove these records?" ) ) )
                return;
        }

        for( auto record : selection_list )
            delete record;

        emit Document()
        .Events()
        .RecordsChanged();
    }


}

void C_Events::OnActionAdd()
{

    int position = -1;
    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    if ( has_selection )
    {
        auto front =
            Document()
            .MainWindow()
            .RecordStructView()
            .Selection()
            .front();
        position =
            Document()
            .Context()
            .Records()
            .GetIndex( front );
    }

    QWidget* dialog;

    if( position >= 0 )
        dialog = new C_UiAddRecord( Document(), position, &Document().MainWindow() );
    else
        dialog = new C_UiAddRecord( Document(), -1,  &Document().MainWindow() );

    dialog->show();
}



void C_Events::OnActionAddSceneItem()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();

    if( ( action_flags & FLAG_ACTION_ADD_SCENE ) &&
            MainWindow().RecordStructView().HasSelection() )
    {
        list<C_Record*> selection_list =
            Document()
            .MainWindow()
            .RecordStructView()
            .Selection();

        for( auto record : selection_list )
        {
            Document()
            .Context()
            .Scene()
            .CreateItem( *record );
        }

        emit Document()
        .Events()
        .SceneChanged();
    }
}

void C_Events::OnActionCopy()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();
    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_COPY ) && has_selection )
    {
        Document()
        .Clipboard()
        .Copy(
            Document()
            .MainWindow()
            .RecordStructView()
            .Selection()
        );

        Document()
        .MainWindow()
        .UpdateMenubar();
    }
}

void C_Events::OnActionPaste()
{

    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();

    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    int position = -1;

    if( action_flags & FLAG_ACTION_PASTE )
    {

        if( has_selection )
        {
            auto selection_list =
                Document()
                .MainWindow()
                .RecordStructView()
                .Selection();

            position =
                Document()
                .MainWindow()
                .RecordStructView()
                .Records()
                .GetIndex( selection_list.front() );
        }

        Document()
        .Clipboard()
        .Paste(
            Document()
            .Context()
            .Records(),
            position
        );

        Document()
        .Clipboard()
        .Clear();

        Document()
        .MainWindow()
        .UpdateMenubar();

        emit Document()
        .Events()
        .RecordsChanged();
    }
}

void C_Events::OnActionCut()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();

    bool has_selection =
        Document()
        .MainWindow()
        .RecordStructView()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_CUT ) && has_selection )
    {
        auto selection_list =
            Document()
            .MainWindow()
            .RecordStructView()
            .Selection();

        for( auto record : selection_list )
        {
            record->SetParent( 0 );
            auto items =
                Document()
                .Scene()
                .FromRecord( *record );

            for( auto item : items )
                delete item;
        }

        Document()
        .Clipboard()
        .Copy( selection_list );

        emit Document()
        .Events()
        .RecordsChanged();
    }

}

void C_Events::OnActionNewDocument()
{
    Document()
    .Clear();
}

void C_Events::OnActionFind()
{
    QWidget* dialog = new C_UiFindRecord( Document(), &MainWindow() );
    dialog->show();
}

void C_Events::OnActionExit()
{
    Document()
    .MainWindow()
    .close();
}

void C_Events::OnActionRunScript()
{
    Document()
    .MainWindow()
    .UpdateWebView();
}



