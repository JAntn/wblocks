#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "ui_mainwindow.h"
#include "FW/UI/ui_add_record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_record_struct_view.h"
#include "FW/UI/ui_find_record.h"
#include "ui_findrecord.h"
#include "ui_record_context_menu.h"
#include "FW/clipboard.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QtWebKitWidgets>

C_UiMainWindow::C_UiMainWindow( QWidget* parent ) :
    QMainWindow( parent ),
    ui( new Ui::C_UiMainWindow )
{
    ui->setupUi( this );
    m_Document = new C_Document( *this );
    m_RecordStructView = new C_UiRecordStructView( Document(), this );
    ui->TableViewLayout->addWidget( m_RecordStructView );
    ui->GraphicsView->setScene(
        &Document()
        .Context()
        .Scene()
        .GraphicsScene() );
    UpdateScriptView();
    ConnectEvents();
}

C_UiMainWindow::~C_UiMainWindow()
{
    delete ui;
}

void C_UiMainWindow::UpdateTableView()
{
    m_RecordStructView->Update();
}

void C_UiMainWindow::UpdateScriptView()
{
    ui->TextEdit->clear();

    for( QString str : Document().Script().StringList() )
        ui->TextEdit->append( str );

    ui->TextEdit->update();
}

void C_UiMainWindow::UpdateSceneView()
{
    // void
}

void C_UiMainWindow::UpdateMenubar()
{
    vector<QAction*> actions =
    {
        ui->ActionCut,
        ui->ActionCopy,
        ui->ActionPaste,
        ui->ActionAdd,
        ui->ActionAdd_to_scene,
        ui->ActionEdit,
        ui->ActionRemove
    };

    vector<long> action_flags =
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
        if( Document().Context().Records().Flags() & (*iter) )
            action->setEnabled( true );
        else
            action->setEnabled( false );

        ++iter;
    }

    if( !Document()
            .MainWindow()
            .RecordStructView()
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
        C_Events::OnActionFileLoad );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionFileSave );

    connect(
        ui->ActionSQLLoad,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSQLLoad );

    connect(
        ui->ActionSQLSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionSQLSave );

    connect(
        ui->ActionScriptSave,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionScriptSave );

    connect(
        ui->ActionAdd,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionAdd );

    connect(
        ui->ActionAdd_to_scene,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionAddSceneItem );

    connect(
        ui->ActionRemove,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionRemove );

    connect(
        ui->ActionCopy,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCopy );

    connect(
        ui->ActionCut,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionCut );

    connect(
        ui->ActionPaste,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionPaste );

    connect(
        ui->ActionRun,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionRunScript );

    connect(
        ui->ActionFind,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionFind );

    connect(
        ui->ActionNew,
        QAction::triggered,
        &Document().Events(),
        C_Events::OnActionNewDocument );
}
