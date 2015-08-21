#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "ui_mainwindow.h"
#include "FW/UI/ui_add_record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_find_record.h"
#include "FW/UI/ui_code_editor.h"
#include "ui_findrecord.h"
#include "ui_record_context_menu.h"
#include "FW/clipboard.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QtWebKitWidgets>
#include "FW/UI/ui_code_editor_container.h"
#include "FW/UI/ui_file_explorer.h"

C_UiMainWindow::C_UiMainWindow( QWidget* parent ) :
    QMainWindow( parent ),
    ui( new Ui::C_UiMainWindow )
{
    m_Document = new C_Document( *this );
    m_RecordExplorer = new C_UiRecordExplorer( Document(), this );
    m_FileExplorer = new C_UiFileExplorer( Document(), "", this );
    m_CodeEditorContainer = new C_UiCodeEditorContainer( this );
    ui->setupUi( this );
    QRect screen_size = QApplication::desktop()->availableGeometry( this );
    setFixedSize( QSize( screen_size.width() * 0.8, screen_size.height() * 0.8 ) );
    ui->RecordExplorerLayout->addWidget( m_RecordExplorer );
    ui->FileExplorerLayout->addWidget( m_FileExplorer );
    ui->EditorLayout->addWidget( m_CodeEditorContainer );
    ui->GraphicsView->setScene(
        &Document()
        .Context()
        .Scene()
        .GraphicsScene() );
    ConnectEvents();
    emit Document().Events().RecordsChanged();
}

C_UiMainWindow::~C_UiMainWindow()
{
    delete ui;
}

void C_UiMainWindow::UpdateRecordExplorer()
{
    m_RecordExplorer->Update();
}

void C_UiMainWindow::UpdateFileExplorer()
{
    m_FileExplorer->Update();
}

void C_UiMainWindow::UpdateClientScriptView()
{
    ui->TextEdit->clear();

    for( QString str : Document().Script().StringList() )
        ui->TextEdit->append( str );

    ui->TextEdit->update();
}

void C_UiMainWindow::UpdateSceneView()
{
    Document()
    .Scene()
    .UpdateLines();
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
            ui->ActionEdit,
            ui->ActionRemove
        };

        QList<long> action_flags =
        {
            FLAG_ACTION_CUT,
            FLAG_ACTION_COPY,
            FLAG_ACTION_PASTE,
            FLAG_ACTION_ADD,
            FLAG_ACTION_ADD_SCENE,
            FLAG_ACTION_EDIT,
            FLAG_ACTION_REMOVE
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
        }

        bool is_empty =
            Document()
            .Clipboard()
            .Empty();

        if( is_empty )
            ui->ActionPaste->setEnabled( false );
    }

    // Update Code Edit menu
    {
        if( CodeEditorContainer().Size() == 0 )
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
    ui->WebView->setHtml( "<html><body></body></html>" );
    ui->WebView->page()->mainFrame()->evaluateJavaScript(
        Document().Script().StringList().join( "" ) );
    ui->WebView->show();
}

void C_UiMainWindow::ConnectEvents()
{
    Document().Events().ConnectEvents();

    connect(
        ui->ActionFileLoad,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionLoadFile );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveFile );

    connect(
        ui->ActionSQLLoad,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionLoadSQL );

    connect(
        ui->ActionSQLSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveSQL );

    connect(
        ui->ActionSaveClientScript,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveClientScript );

    connect(
        ui->ActionUpdateClientScript,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionUpdateClientScript );

    connect(
        ui->ActionRunClientScript,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionRunClientScript );

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
        C_Events::OnActionNewFile );

    connect(
        ui->ActionNewEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionNewEditorFile );

    connect(
        ui->ActionCloseEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCloseEditorFile );

    connect(
        ui->ActionCloseAllEditorFiles,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCloseAllEditorFiles );

    connect(
        ui->ActionSaveEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveEditorFile );

    connect(
        ui->ActionSaveAllEditorFiles,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSaveAllEditorFiles );

    connect(
        ui->ActionLoadEditorFile,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionLoadEditorFile );
}

