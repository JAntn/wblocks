#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_add_record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_editor_container.h"
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

C_UiMainWindow::C_UiMainWindow( C_Controller& controller, QWidget* parent ):
    QMainWindow( parent ),
    m_Controller( &controller ),
    ui( new Ui::C_UiMainWindow )
{
    controller.SetMainWindow( *this );

    m_RecordExplorer = 0;
    m_FileExplorer = 0;
    m_Document = 0;
    m_PropertiesWidget = 0;

    // SETUP USER INTERFACE

    ui->setupUi( this );

    m_RecordExplorer = new C_UiRecordExplorer( controller.Document().Context(), Controller(), this );
    m_FileExplorer = new C_UiFileExplorer( controller, this );
    m_TextEditorContainer = new C_UiEditorContainer( controller, this );

    ui->RecordExplorerLayout->addWidget( m_RecordExplorer );
    ui->EditorLayout->addWidget( m_TextEditorContainer );
    ui->FileExplorerLayout->addWidget( m_FileExplorer );
    ui->GraphicsView->setScene( &Controller().Document().Scene().Graphics() );

    QRect screen_size = QApplication::desktop()->availableGeometry( this );
    resize( QSize( screen_size.width() * 0.8, screen_size.height() * 0.8 ) );
    SetTitle( controller.Config().ProjectFileName() );

    InitConnections();

    emit Controller().RecordsChanged();
    SetCurrentTab( MAINWINDOW_TAB_SCENE );
}

C_UiMainWindow::~C_UiMainWindow()
{
    Controller().Config().SetProjectFileName( Controller().Document().FileName() );
    Controller().Config().SetProjectPath( Controller().Document().Path() );
    Controller().Config().Save();
    delete ui;
}

void C_UiMainWindow::InitConnections()
{
    Controller().ConnectSlots();

    connect(
        ui->ActionExit,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionExit );

    connect(
        ui->ActionFileLoad,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionLoadProjectFile );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionSaveProjectFile );

    connect(
        ui->ActionSQLLoad,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionLoadProjectSQL );

    connect(
        ui->ActionSQLSave,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionSaveProjectSQL );

    connect(
        ui->ActionSaveClientScript,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionSaveHtmlCode );

    connect(
        ui->ActionUpdateClientScript,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionUpdateHtmlCode );

    connect(
        ui->ActionRunClientScript,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionRunHtmlCode );

    connect(
        ui->ActionAdd,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionAddRecord );

    connect(
        ui->ActionAdd_to_scene,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionAddSceneItem );

    connect(
        ui->ActionProperties,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionChangePropertyWidget );

    connect(
        ui->ActionOpen_In_Editor,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionOpenRecordInEditor );

    connect(
        ui->ActionRemove,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionRemoveRecord );

    connect(
        ui->ActionCopy,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionCopyRecord );

    connect(
        ui->ActionCut,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionCutRecord );

    connect(
        ui->ActionPaste,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionPasteRecord );

    connect(
        ui->ActionNew,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionNewProjectFile );

    connect(
        ui->ActionNewEditorFile,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionNewFile );

    connect(
        ui->ActionCloseEditorFile,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionCloseFile );

    connect(
        ui->ActionCloseAllEditorFiles,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionCloseAllFiles );

    connect(
        ui->ActionSaveEditorFile,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionSaveFile );

    connect(
        ui->ActionSaveAllEditorFiles,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionSaveAllFiles );

    connect(
        ui->ActionLoadEditorFile,
        QAction::triggered,
        &Controller(),
        C_Controller::OnActionLoadFile );
}

void C_UiMainWindow::closeEvent( QCloseEvent* )
{
    if( C_Controller::AcceptMessage( "Save project changes?" ) )
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

void C_UiMainWindow::SetTitle( QString title )
{
    if( !title.isEmpty() )
        title.prepend( " - " );

    setWindowTitle( "JSBlocks" + title );
}

void C_UiMainWindow::SetCurrentTab( int index )
{
    ui->TabWidget->setCurrentIndex( index );
}

void C_UiMainWindow::SetPropertyWidget( QWidget* widget )
{
    if( m_PropertiesWidget != 0 )
        delete m_PropertiesWidget;

    m_PropertiesWidget = widget;
    m_PropertiesWidget->setParent( this );
    ui->PropertiesLayout->addWidget( widget );
}

void C_UiMainWindow::OpenEditorWidget( C_UiEditor* widget )
{
    TextEditorContainer().Append( widget );
    SetCurrentTab( MAINWINDOW_TAB_EDITOR );
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
    ui->TextEdit->setPlainText( Controller().Document().Html() );
    ui->TextEdit->update();
}

void C_UiMainWindow::UpdateSceneView()
{
    Controller().Document().Scene().UpdateLines();
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

void C_UiMainWindow::UpdateWebView()
{
    Controller().Document().UpdateHtml();

    ui->WebView->setHtml( Controller().Document().Html() );
    ui->WebView->show();
}
