#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_add_record.h"
#include "FW/SC/scene.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "FW/UI/SH/ui_syntax_highlighter_factory.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/UI/ED/ui_html_blocks_editor.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/controller.h"
#include "FW/config.h"
#include "FW/clipboard.h"
#include "FW/htmlbuilder.h"
#include "ui_record_contextmenu.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QtWebKitWidgets>


TypeUiMainWindow::TypeUiMainWindow( TypeController& controller, QWidget* parent ):
    QMainWindow( parent ),
    TypeVariant( 0 ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiMainWindow )
{
    controller.SetMainWindow( *this );

    m_RecordExplorer = 0;
    m_FileExplorer = 0;
    m_Document = 0;
    m_PropertiesWidget = 0;
    m_HtmlBlocksEditor = 0;

    // SETUP USER INTERFACE

    ui->setupUi( this );

    m_RecordExplorer = new TypeUiRecordExplorer( controller.Document().Context(), Controller(), this );
    m_FileExplorer = new TypeUiFileExplorer( controller, this );
    m_TextEditorContainer = new TypeUiEditorContainer( controller, this );

    ui->RecordExplorerLayout->addWidget( m_RecordExplorer );
    ui->EditorLayout->addWidget( m_TextEditorContainer );
    ui->FileExplorerLayout->addWidget( m_FileExplorer );
    ui->GraphicsView->setScene( &Controller().Document().Scene().Graphics() );

    // !!!

    m_HtmlBlocksEditor = new TypeUiHtmlBlocksEditor(
        controller,
        controller.NewHtmlBlocksEditorId( controller.Document().FileName() ),
        controller.Document().FileName(),
        controller.Document().FileName().split( "/" ).back(),
        this,
        &TypeUiEditor::empty_save_callback,
        controller.SyntaxHighlighterFactory().NewInstance( "HTML" ) );

    ui->HtmlTextLayout->addWidget( m_HtmlBlocksEditor );

    // TODO: multiple module support implementation
    // + TypeUiHtmlBlocksEditor: to implement interface to multiple module tab container
    // + to implement a tab container class
    // + to implement multiple document load n save etc

    QRect screen_size = QApplication::desktop()->availableGeometry( this );
    resize( QSize( screen_size.width() * 0.8, screen_size.height() * 0.8 ) );
    SetTitle( controller.Config().ProjectFileName() );

    InitConnections();

    emit Controller().RecordsChanged();
    SetCurrentTab( MAINWINDOW_TAB_SCENE );

    // !!!
    HtmlBlocksEditor().SetFileTitle( controller.Document().FileName() );
    HtmlBlocksEditor().SetHasChanged( false );
    //
}

TypeUiMainWindow::~TypeUiMainWindow()
{
    Controller().Config().SetProjectFileName( Controller().Document().FileName() );
    Controller().Config().SetProjectPath( Controller().Document().Path() );
    Controller().Config().Save();
    delete ui;
}

void TypeUiMainWindow::InitConnections()
{
    Controller().ConnectSlots();

    connect(
        ui->ActionExit,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionExit );

    connect(
        ui->ActionFileLoad,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionLoadProjectFile );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionSaveProjectFile );

    connect(
        ui->ActionSQLLoad,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionLoadProjectSQL );

    connect(
        ui->ActionSQLSave,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionSaveProjectSQL );

    connect(
        ui->ActionSaveClientScript,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionSaveHtmlBlocks );

    connect(
        ui->ActionUpdateClientScript,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionUpdateHtmlBlocks );

    connect(
        ui->ActionRunClientScript,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRunHtmlBlocks );

    connect(
        ui->ActionAdd,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionAddRecord );

    connect(
        ui->ActionAdd_to_scene,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionAddSceneItem );

    connect(
        ui->ActionProperties,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionChangePropertyWidget );

    connect(
        ui->ActionOpen_In_Editor,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionOpenRecordInEditor );

    connect(
        ui->ActionRemove,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRemoveRecord );

    connect(
        ui->ActionCopy,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionCopyRecord );

    connect(
        ui->ActionCut,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionCutRecord );

    connect(
        ui->ActionPaste,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionPasteRecord );

    connect(
        ui->ActionNew,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionNewProjectFile );

    connect(
        ui->ActionNewEditorFile,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionNewFile );

    connect(
        ui->ActionCloseEditorFile,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionCloseFile );

    connect(
        ui->ActionCloseAllEditorFiles,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionCloseAllFiles );

    connect(
        ui->ActionSaveEditorFile,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionSaveFile );

    connect(
        ui->ActionSaveAllEditorFiles,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionSaveAllFiles );

    connect(
        ui->ActionLoadEditorFile,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionLoadFile );
}

void TypeUiMainWindow::closeEvent( QCloseEvent* )
{
    if( TypeController::AcceptMessage( "Save project changes?" ) )
    {
        QString file_name = Controller().Document().FileName();

        if( file_name.isEmpty() )
        {
            file_name =
                QFileDialog::getSaveFileName(
                    this,
                    tr( "Save File" ),
                    "untitled.prj",
                    tr( "Project Files (*.prj, *.sql)" )
                );
        }

        if( file_name.isEmpty() )
            qDebug() << "File Selection failed";
        else
        {
            TextEditorContainer().SaveAll();

            if( file_name.split( "." ).back() == "prj" )
                Controller().Document().SaveFile( file_name );
            else if( file_name.split( "." ).back() == "sql" )
                Controller().Document().SaveSQL( file_name );
        }
    }
}

void TypeUiMainWindow::SetTitle( QString title )
{
    if( !title.isEmpty() )
        title.prepend( " - " );

    setWindowTitle( "JSBlocks" + title );
}

void TypeUiMainWindow::SetCurrentTab( int index )
{
    ui->TabWidget->setCurrentIndex( index );
}

void TypeUiMainWindow::SetPropertyWidget( QWidget* widget )
{
    if( m_PropertiesWidget != 0 )
        delete m_PropertiesWidget;

    m_PropertiesWidget = widget;
    m_PropertiesWidget->setParent( this );
    ui->PropertiesLayout->addWidget( widget );
}

void TypeUiMainWindow::OpenEditorWidget( TypeUiEditor* widget )
{
    TextEditorContainer().Append( widget );
    SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

void TypeUiMainWindow::UpdateRecordExplorer()
{
    if( m_RecordExplorer != 0 )
        m_RecordExplorer->Update();
}

void TypeUiMainWindow::UpdateFileExplorer()
{
    if( m_FileExplorer != 0 )
        m_FileExplorer->Update();
}

void TypeUiMainWindow::UpdateHtmlTextView()
{
    HtmlBlocksEditor().UpdateText();
}

void TypeUiMainWindow::UpdateSceneView()
{
    Controller().Document().Scene().UpdateLines();
}

void TypeUiMainWindow::UpdateMenubar()
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
            if( Controller().Document().Context().Records().Flags() & ( *iter ) )
                action->setEnabled( true );
            else
                action->setEnabled( false );

            ++iter;
        }

        if( !RecordExplorer().HasSelection() )
        {
            ui->ActionCopy->setEnabled( false );
            ui->ActionCut->setEnabled( false );
            ui->ActionAdd_to_scene->setEnabled( false );
            ui->ActionRemove->setEnabled( false );
            ui->ActionOpen_In_Editor->setEnabled( false );
            ui->ActionProperties->setEnabled( false );

        }

        if( Controller().Clipboard().Empty() )
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

void TypeUiMainWindow::UpdateWebView()
{
    Controller().Document().UpdateHtml();

    ui->WebView->setHtml( Controller().Document().Html() );
    ui->WebView->show();
}
