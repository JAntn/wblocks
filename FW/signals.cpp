#include "FW/document.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_struct_view.h"
#include "FW/UI/ui_add_record.h"
#include <QFileDialog>
#include "FW/RC/record_struct.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include <QList>

C_Signals::C_Signals( C_Document& document, C_UiMainWindow& main_window, QObject* parent )
    : QObject( parent )
{
    m_Document = &document;
    m_MainWindow = &main_window;
}

C_Signals::~C_Signals()
{
    // void
}

void C_Signals::OnRecordsChanged()
{
    MainWindow().UpdateTableView();

    Document().UpdateScript();
    Document().UpdateScene();
}

void C_Signals::OnScriptChanged()
{
    MainWindow().UpdateScriptView();
}

void C_Signals::OnSceneChanged()
{
    MainWindow().UpdateSceneView();
}

void C_Signals::OnActionFileLoad()
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

void C_Signals::OnActionFileSave()
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

void C_Signals::OnActionSQLLoad()
{
    QString file_name = QFileDialog::getOpenFileName( &MainWindow(),
                        tr( "Load SQL Database File" ),
                        "",
                        tr( "SQL Files (*.sql)" ) );

    if( file_name.isEmpty() )
        return;

    Document().DatabaseLoad( file_name );
}

void C_Signals::OnActionSQLSave()
{
    QString file_name = QFileDialog::getSaveFileName( &MainWindow(),
                        tr( "Save SQL Database File" ),
                        tr( "untitled.sql" ),
                        tr( "SQL Files (*.sql)" ) );

    if( file_name.isEmpty() )
        return;

    Document().DatabaseSave( file_name );
}

void C_Signals::OnActionScriptSave()
{
    QString file_name = QFileDialog::getSaveFileName( &Document().MainWindow(),
                        tr( "Save Java Script File" ),
                        tr( "untitled.js" ),
                        tr( "JS Files (*.js)" ) );

    if( file_name.isEmpty() )
        return;

    Document().Script().Generate( Document().Records() );
    emit Document().Signals().ScriptChanged();
    C_Document::SaveTextFile( file_name, Document().Script().StringList().join( "" ) );
}

void C_Signals::ConnectSignals()
{
    connect(
        this,
        C_Signals::RecordsChanged,
        this,
        C_Signals::OnRecordsChanged );

    connect(
        this,
        C_Signals::SceneChanged,
        this,
        C_Signals::OnSceneChanged );

    connect(
        this,
        C_Signals::ScriptChanged,
        this,
        C_Signals::OnScriptChanged );
}


void C_Signals::OnActionEdit()
{
    int position = EventData().at( 0 ).toInt();

    auto record = Document()
                  .Context()
                  .Records()
                  .FromIndex( position );

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    record->ShowEditor( Document() );
}

void C_Signals::OnActionRemove()
{
    list<C_Record*> selection_list =
        Document()
        .MainWindow()
        .RecordStructView()
        .Selection();

    if( selection_list.size() == 1 )
    {
        if( C_Document::AcceptMessage( tr( "Do you want to remove this record?" ) ) )
            delete * selection_list.begin();
    }
    else
    {
        if( C_Document::AcceptMessage( tr( "Do you want to remove these records?" ) ) )
        {
            for( auto record : selection_list )
                delete record;
        }
    }

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    emit Document()
    .Signals()
    .RecordsChanged();
}

void C_Signals::OnActionAdd()
{
    QWidget* dialog;
    int position = EventData().at( 0 ).toInt();

    if( position >= 0 )
        dialog = new C_UiAddRecord( Document(), position );
    else
        dialog = new C_UiAddRecord( Document() );

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    dialog->show();
}

void C_Signals::OnActionAddSceneItem()
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

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    emit Document()
    .Signals()
    .SceneChanged();
}

void C_Signals::OnActionCopy()
{
    list<C_Record*> selection_list =
        Document()
        .MainWindow()
        .RecordStructView()
        .Selection();

    if( selection_list.empty() )
        return;

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    Document()
    .Clipboard()
    .Copy( selection_list );

}

void C_Signals::OnActionPaste()
{
    int position = EventData().at( 0 ).toInt();

    Document()
    .Clipboard()
    .Paste(
        Document()
        .Context()
        .Records(),
        position
    );

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    emit Document()
    .Signals()
    .RecordsChanged();
}

void C_Signals::OnActionCut()
{
    list<C_Record*> selection_list =
        Document()
        .MainWindow()
        .RecordStructView()
        .Selection();

    if( selection_list.empty() )
        return;

    for( auto record : selection_list )
    {
        record->SetParent( 0 );
        auto items = Document().Scene().FromRecord( *record );

        for( auto item : items )
            delete item;
    }

    Document()
    .MainWindow()
    .RecordStructView()
    .ClearSelection();

    Document()
    .Clipboard()
    .Copy( selection_list );

    emit Document()
    .Signals()
    .RecordsChanged();
}





