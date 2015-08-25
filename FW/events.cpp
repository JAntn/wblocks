#include "FW/RC/record_struct.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include "FW/document.h"
#include "FW/UI/ui_file_text_editor.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_find_record.h"
#include "FW/UI/ui_text_editor_container.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QFileDialog>
#include <QWebFrame>


C_Events::C_Events( C_Document& document, C_UiMainWindow& main_window ):
    QObject( &main_window )
{
    m_Document = &document;
    m_MainWindow = &main_window;
}

C_Events::~C_Events()
{
    // void
}

void C_Events::InitConnections()
{
    connect(
        this,
        C_Events::DirectoryChanged,
        this,
        C_Events::OnDirectoryChanged );

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
        C_Events::ClientScriptChanged,
        this,
        C_Events::OnClientScriptChanged );

    connect(
        this,
        C_Events::RecordExplorerChanged,
        this,
        C_Events::OnRecordExplorerChanged );

    connect(
        this,
        C_Events::FileExplorerChanged,
        this,
        C_Events::OnFileExplorerChanged );

    connect(
        this,
        C_Events::TextEditorContainerChanged,
        this,
        C_Events::OnTextEditorContainerChanged );
}

void C_Events::OnDirectoryChanged()
{
    MainWindow().UpdateFileExplorer();
}

void C_Events::OnRecordExplorerChanged()
{
    MainWindow().UpdateMenubar();
}

void C_Events::OnFileExplorerChanged()
{
    MainWindow().UpdateMenubar();
}

void C_Events::OnRecordsChanged()
{
    MainWindow().UpdateRecordExplorer();
    Document().UpdateHtmlDoc();
    Document().UpdateScene();
}

void C_Events::OnClientScriptChanged()
{
    MainWindow().UpdateHtmlDocView();
}

void C_Events::OnTextEditorContainerChanged()
{
    MainWindow().UpdateMenubar();
}

void C_Events::OnSceneChanged()
{
    MainWindow().UpdateSceneView();
}

void C_Events::OnActionLoadProjectFile()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "Load File" ),
            Document().FileName(),
            tr( "Project Files (*.prj)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    QFile file( file_name );
    Document().LoadFile( file );

}

void C_Events::OnActionSaveProjectFile()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save File" ),
            Document().FileName(),
            tr( "Project Files (*.prj)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    QFile file( file_name );
    Document().SaveFile( file );
}

void C_Events::OnActionLoadProjectSQL()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "Load SQL Database File" ),
            "",
            tr( "SQL Files (*.sql)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Document().LoadSQL( file_name );
}

void C_Events::OnActionSaveProjectSQL()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save SQL Database File" ),
            tr( "untitled.sql" ),
            tr( "SQL Files (*.sql)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Document().SaveSQL( file_name );
}

void C_Events::OnActionSaveClientScript()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &Document().MainWindow(),
            tr( "Save Java Script File" ),
            tr( "untitled.js" ),
            tr( "JS Files (*.js)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Document().Script().Parse( Document().Root() );
    emit Document().Events().ClientScriptChanged();
    C_Document::SaveTextFile(
        file_name,
        Document().Script().StringList().join( "" )
    );
}

void C_Events::OnActionEditRecordProperties()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags() ;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_PROPERTIES ) && has_selection )
    {
        C_Record* record =
            static_cast<C_Record*>(
                *MainWindow()
                .RecordExplorer()
                .Selection()
                .begin()
            );

        if( !( record->Flags() & FLAG_ACTION_PROPERTIES ) )
        {
            qDebug() << "FLAG_ACTION_PROPERTIES is disabled on Record:"
                     << record->Name();
            return;
        }

        record->EditProperties( Document() );
    }
    else
    {
        qDebug() << "FLAG_ACTION_PROPERTIES is disabled on Struct:"
                 << Document().Context().Records().Name();
    }
}

void C_Events::OnActionRemoveRecord()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags() ;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection )
    {
        auto selection_list =
            Document()
            .MainWindow()
            .RecordExplorer()
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

        for( C_Record* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_REMOVE ) )
            {
                qDebug() << "FLAG_ACTION_REMOVE is disabled on Record:"
                         << record->Name();
                return;
            }
        }

        for( C_Record* record : selection_list )
            delete record;

        emit Document().Events().RecordsChanged();
    }
    else
    {
        qDebug() << "FLAG_ACTION_REMOVE is disabled on Struct:"
                 << Document().Context().Records().Name();
    }
}

void C_Events::OnActionAddRecord()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags() ;

    if( !( action_flags & FLAG_ACTION_ADD ) )
    {
        qDebug() << "FLAG_ACTION_ADD is disabled on Struct:"
                 << Document().Context().Records().Name();
        return;
    }

    int position = -1;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();

    if ( has_selection )
    {
        auto front =
            Document()
            .MainWindow()
            .RecordExplorer()
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
            MainWindow().RecordExplorer().HasSelection() )
    {
        auto selection_list =
            Document()
            .MainWindow()
            .RecordExplorer()
            .Selection();

        for( C_Record* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_ADD_SCENE ) )
            {
                qDebug() << "FLAG_ACTION_ADD_SCENE is disabled on Record:"
                         << record->Name();
                return;
            }
        }

        for( C_Record* record : selection_list )
        {
            Document()
            .Context()
            .Scene()
            .CreateItem( *record );
        }

        emit Document().Events().SceneChanged();
        MainWindow().SetCurrentTab( MAINWINDOW_TAB_SCENE );
    }
    else
    {
        qDebug() << "FLAG_ACTION_ADD_SCENE is disabled on Struct:"
                 << Document().Context().Records().Name();
        return;
    }
}

void C_Events::OnActionCopyRecord()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();



    if( ( action_flags & FLAG_ACTION_COPY ) && has_selection )
    {
        auto selection_list =
            Document()
            .MainWindow()
            .RecordExplorer()
            .Selection();

        for( C_Record* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_CUT ) )
            {
                qDebug() << "FLAG_ACTION_CUT is disabled on Record:"
                         << record->Name();
                return;
            }
        }

        Document().Clipboard().Copy( selection_list );
        Document().MainWindow().UpdateMenubar();
    }
    else
    {
        qDebug() << "FLAG_ACTION_COPY is disabled on Struct:"
                 << Document().Context().Records().Name();
        return;
    }
}

void C_Events::OnActionPasteRecord()
{

    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();

    int position = -1;

    if( action_flags & FLAG_ACTION_PASTE )
    {

        if( has_selection )
        {
            auto selection_list =
                Document()
                .MainWindow()
                .RecordExplorer()
                .Selection();

            position =
                Document()
                .MainWindow()
                .RecordExplorer()
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

        Document().Clipboard().Clear();
        emit Document().Events().RecordsChanged();
    }
    else
    {
        qDebug() << "FLAG_ACTION_PASTE is disabled on Struct:"
                 << Document().Context().Records().Name();
        return;
    }
}

void C_Events::OnActionCutRecord()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags();

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_CUT ) && has_selection )
    {
        auto selection_list =
            Document()
            .MainWindow()
            .RecordExplorer()
            .Selection();

        for( C_Record* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_CUT ) )
            {
                qDebug() << "FLAG_ACTION_CUT is disabled on Record:"
                         << record->Name();
                return;
            }
        }

        for( C_Record* record : selection_list )
        {
            record->SetParent( 0 );

            auto items =
                Document()
                .Scene()
                .FromRecord( *record );

            for( auto item : items )
                delete item;
        }

        Document().Clipboard().Copy( selection_list );
        emit Document().Events().RecordsChanged();
    }
    else
    {
        qDebug() << "FLAG_ACTION_CUT is disabled on Struct:"
                 << Document().Context().Records().Name();
        return;
    }
}

void C_Events::OnActionOpenRecordInEditor()
{
    long action_flags =
        Document()
        .Context()
        .Records()
        .Flags() ;

    bool has_selection =
        Document()
        .MainWindow()
        .RecordExplorer()
        .HasSelection();

    if( ( action_flags & FLAG_ACTION_OPEN ) && has_selection )
    {
        C_Record* record =
            static_cast<C_Record*>(
                *MainWindow()
                .RecordExplorer()
                .Selection()
                .begin()
            );

        if( !( record->Flags() & FLAG_ACTION_OPEN ) )
        {
            qDebug() << "FLAG_ACTION_OPEN is disabled on Record:"
                     << record->Name();
            return;
        }

        record->OpenInEditor( Document() );
    }
    else
    {
        qDebug() << "FLAG_ACTION_OPEN is disabled on Struct:"
                 << Document().Context().Records().Name();
    }
}

void C_Events::OnActionNewProjectFile()
{
    Document().Clear();
}

void C_Events::OnActionFindRecord()
{
    QWidget* dialog = new C_UiFindRecord( Document(), &MainWindow() );
    dialog->show();
}

void C_Events::OnActionNewFile()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "New File" ),
            tr( "untitled.js" ),
            tr( "JS Files (*.js)" )
        );

    if( file_name.isEmpty() )
        return;

    C_Document::SaveTextFile( file_name, "//FILE: " + file_name.split( "/" ).back() );

    QString editor_id = "FILE:TEXT:" + file_name;

    MainWindow().TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
    emit TextEditorContainerChanged();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

void C_Events::OnActionCloseFile()
{
    if( C_Document::AcceptMessage( tr( "Save changes?" ) ) )
        MainWindow().TextEditorContainer().SaveStateCurrent();

    MainWindow().TextEditorContainer().CloseCurrent();
    emit TextEditorContainerChanged();
}

void C_Events::OnActionCloseAllFiles()
{
    if( C_Document::AcceptMessage( tr( "Save changes?" ) ) )
        MainWindow().TextEditorContainer().SaveStateAll();

    MainWindow().TextEditorContainer().CloseAll();
    emit TextEditorContainerChanged();
}

void C_Events::OnActionSaveFile()
{
    MainWindow().TextEditorContainer().SaveStateCurrent();
}

void C_Events::OnActionSaveAllFiles()
{
    MainWindow().TextEditorContainer().SaveStateAll();
}

void C_Events::OnActionLoadFile()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "New File" ),
            tr( "untitled.js" ),
            tr( "JS Files (*.js)" )
        );

    if( !QFileInfo( file_name ).exists() )
    {
        C_Document::Message( tr( "File doesn't exists" ) );
        return;
    }

    QString editor_id = "FILE:TEXT:" + file_name;

    if( MainWindow().TextEditorContainer().HasId( editor_id ) )
    {
        if( C_Document::AcceptMessage( tr( "File already opened.\n\nLoad again?" ) ) )
        {
            MainWindow().TextEditorContainer().Close( editor_id );
            MainWindow().TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
            emit TextEditorContainerChanged();
            MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );
        }

        return;
    }

    MainWindow().TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
    emit TextEditorContainerChanged();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

void C_Events::OnActionExit()
{
    MainWindow().close();
}

void C_Events::OnActionRunClientScript()
{
    MainWindow().UpdateWebView();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_OUTPUT );
}

void C_Events::OnActionUpdateClientScript()
{
    MainWindow().UpdateHtmlDocView();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_CLIENT );
}



