#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_add_record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_find_record.h"
#include "FW/UI/ui_file_text_editor.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/config.h"
#include "FW/clipboard.h"
#include "FW/htmlbuilder.h"
#include "ui_findrecord.h"
#include "ui_record_context_menu.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QtWebKitWidgets>

C_UiMainWindow::C_UiMainWindow( QWidget* parent ):
    QMainWindow( parent ),
    ui( new Ui::C_UiMainWindow )
{
    QFile project_file;

    m_RecordExplorer = 0;
    m_FileExplorer = 0;
    m_Document = 0;

    // ROOT OBJECT

    m_Config = new C_Config( QDir().canonicalPath() );
    m_Config->Load();

    // BUILD EMPTY DOCUMENT

    m_Document = new C_Document( Config().ProjectFileName(), Config().ProjectPath(), *this, m_Config );

    // FILL DOCUMENT USING STORED CONFIGURATION

    bool check_config =
        QFileInfo( Config().ProjectPath() ).exists() &&
        QFileInfo( Config().ProjectFileFullName() ).exists();

    if( !check_config )
    {
        Document().SetPath( "" );
        Document().SetFileName( "" );

        Config().SetProjectPath( Document().Path() );
        Config().SetProjectFileName( Document().FileName() );

        C_Record* string_record =
            Document().Root().CreateRecord(
                "SampleString",
                "Welcome to JS Blocks.\n This is a sample string", "String"
            );

        Document().Scene().CreateItem( *string_record );
    }
    else
    {
        QDir().setCurrent( Config().ProjectPath() );
        project_file.setFileName( Config().ProjectFileFullName() );
    }

    // SETUP USER INTERFACE

    ui->setupUi( this );

    m_RecordExplorer = new C_UiRecordExplorer( Document(), this );
    m_FileExplorer = new C_UiFileExplorer( Document(), this );
    m_TextEditorContainer = new C_UiTextEditorContainer( this );

    ui->RecordExplorerLayout->addWidget( m_RecordExplorer );
    ui->EditorLayout->addWidget( m_TextEditorContainer );
    ui->FileExplorerLayout->addWidget( m_FileExplorer );
    ui->GraphicsView->setScene( &Document().Scene().Graphics() );

    QRect screen_size = QApplication::desktop()->availableGeometry( this );
    setFixedSize( QSize( screen_size.width() * 0.8, screen_size.height() * 0.8 ) );

    if( check_config )
        Document().LoadFile( project_file );

    InitConnections();

    emit Document().Events().RecordsChanged();
    SetCurrentTab( MAINWINDOW_TAB_SCENE );
}

C_UiMainWindow::~C_UiMainWindow()
{
    m_Config->Save();
    delete m_Config;
    delete ui;
}

void C_UiMainWindow::InitConnections()
{
    Document().Events().InitConnections();

    connect(
        ui->ActionExit,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionExit );

    connect(
        ui->ActionFileLoad,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionLoadProjectFile );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveProjectFile );

    connect(
        ui->ActionSQLLoad,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionLoadProjectSQL );

    connect(
        ui->ActionSQLSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveProjectSQL );

    connect(
        ui->ActionSaveClientScript,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveHtmlCode );

    connect(
        ui->ActionUpdateClientScript,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionUpdateHtmlCode );

    connect(
        ui->ActionRunClientScript,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionRunHtmlCode );

    connect(
        ui->ActionAdd,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionAddRecord );

    connect(
        ui->ActionAdd_to_scene,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionAddSceneItem );

    connect(
        ui->ActionProperties,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionEditRecordProperties );

    connect(
        ui->ActionOpen_In_Editor,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionOpenRecordInEditor );

    connect(
        ui->ActionRemove,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionRemoveRecord );

    connect(
        ui->ActionCopy,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCopyRecord );

    connect(
        ui->ActionCut,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCutRecord );

    connect(
        ui->ActionPaste,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionPasteRecord );

    connect(
        ui->ActionFind,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionFindRecord );

    connect(
        ui->ActionNew,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionNewProjectFile );

    connect(
        ui->ActionNewEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionNewFile );

    connect(
        ui->ActionCloseEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCloseFile );

    connect(
        ui->ActionCloseAllEditorFiles,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCloseAllFiles );

    connect(
        ui->ActionSaveEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveFile );

    connect(
        ui->ActionSaveAllEditorFiles,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveAllFiles );

    connect(
        ui->ActionLoadEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionLoadFile );
}

void C_UiMainWindow::closeEvent( QCloseEvent* )
{
    if( C_Document::AcceptMessage( "Save project changes?" ) )
    {
        QString file_name = Document().FileName();

        if( file_name.isEmpty() )
        {
            file_name =
                QFileDialog::getSaveFileName(
                    this,
                    tr( "Save File" ),
                    "untitled.prj",
                    tr( "Project Files (*.prj)" )
                );
        }

        if( file_name.isEmpty() )
            qDebug() << "File Selection failed";
        else
        {
            TextEditorContainer().SaveStateAll();
            QFile file( file_name );
            Document().SaveFile( file );
        }
    }
}

void C_UiMainWindow::SetTitle( QString title )
{
    setWindowTitle( "JSBlocks - " + title );
}

void C_UiMainWindow::SetCurrentTab( int index )
{
    ui->TabWidget->setCurrentIndex( index );
}

void C_UiMainWindow::UpdateRecordExplorer()
{
    if( m_RecordExplorer != 0 )
        m_RecordExplorer->Update();
}

void C_UiMainWindow::UpdateFileExplorer()
{
    if( m_FileExplorer != 0 )
        m_FileExplorer->Update();
}

void C_UiMainWindow::UpdateHtmlCodeView()
{
    ui->TextEdit->setPlainText( Document().Html() );
    ui->TextEdit->update();
}

void C_UiMainWindow::UpdateSceneView()
{
    Document().Scene().UpdateLines();
}

void C_UiMainWindow::UpdateMenubar()
{
    // Update Record menu
    {
        QList<QAction*> actions =
        {
            ui->ActionCut,
            ui->ActionCopy,
            ui->ActionPaste,
            ui->ActionAdd,
            ui->ActionAdd_to_scene,
            ui->ActionProperties,
            ui->ActionRemove,
            ui->ActionOpen_In_Editor
        };

        QList<long> action_flags =
        {
            FLAG_ACTION_CUT,
            FLAG_ACTION_COPY,
            FLAG_ACTION_PASTE,
            FLAG_ACTION_ADD,
            FLAG_ACTION_ADD_SCENE,
            FLAG_ACTION_PROPERTIES,
            FLAG_ACTION_REMOVE,
            FLAG_ACTION_OPEN
        };

        auto iter = action_flags.begin();

        for( auto action : actions )
        {
            if( Document().Context().Records().Flags() & ( *iter ) )
                action->setEnabled( true );
            else
                action->setEnabled( false );

            ++iter;
        }

        if( !Document()
                .MainWindow()
                .RecordExplorer()
                .HasSelection() )
        {
            ui->ActionCopy->setEnabled( false );
            ui->ActionCut->setEnabled( false );
            ui->ActionAdd_to_scene->setEnabled( false );
            ui->ActionRemove->setEnabled( false );
            ui->ActionOpen_In_Editor->setEnabled( false );
            ui->ActionProperties->setEnabled( false );

        }

        bool is_empty =
            Document()
            .Clipboard()
            .Empty();

        if( is_empty )
            ui->ActionPaste->setEnabled( false );
    }

    // Update Text Edit Container
    {
        if( TextEditorContainer().Size() == 0 )
        {
            ui->ActionSaveAllEditorFiles->setEnabled( false );
            ui->ActionSaveEditorFile->setEnabled( false );
            ui->ActionCloseAllEditorFiles->setEnabled( false );
            ui->ActionCloseEditorFile->setEnabled( false );
        }
        else
        {
            ui->ActionSaveAllEditorFiles->setEnabled( true );
            ui->ActionSaveEditorFile->setEnabled( true );
            ui->ActionCloseAllEditorFiles->setEnabled( true );
            ui->ActionCloseEditorFile->setEnabled( true );
        }
    }
}

void C_UiMainWindow::UpdateWebView()
{
    Document().UpdateHtml();

    ui->WebView->setHtml( Document().Html() );
    ui->WebView->show();
}
