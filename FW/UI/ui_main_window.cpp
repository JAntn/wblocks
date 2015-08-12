#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "ui_mainwindow.h"
#include "FW/UI/ui_add_record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_record_struct_view.h"
#include "FW/UI/ui_find_record.h"
#include "ui_findrecord.h"
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
    ui->GraphicsView->setScene( &Document().Context().Scene().GraphicsScene() );
    UpdateScriptView();
    ConnectSignals();
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
    // ...
}

void C_UiMainWindow::ConnectSignals()
{
    Document().Signals().ConnectSignals();

    connect(
        ui->ActionFileLoad,
        QAction::triggered,
        &Document().Signals(),
        C_Signals::OnActionFileLoad );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Document().Signals(),
        C_Signals::OnActionFileSave );

    connect(
        ui->ActionSQLLoad,
        QAction::triggered,
        &Document().Signals(),
        C_Signals::OnActionSQLLoad );

    connect(
        ui->ActionSQLSave,
        QAction::triggered,
        &Document().Signals(),
        C_Signals::OnActionSQLSave );

    connect(
        ui->ActionScriptSave,
        QAction::triggered,
        &Document().Signals(),
        C_Signals::OnActionScriptSave );
}

void C_UiMainWindow::on_ActionNew_triggered()
{
    Document().Clear();
}

void C_UiMainWindow::on_ActionCopy_triggered()
{
    if( ! ( Document().Context().Records().Flags() & FLAG_ACTION_COPY ) )
        return;

    bool empty = Document()
                 .MainWindow()
                 .RecordStructView()
                 .Selection()
                 .empty();

    if( empty )
        return;

    Document().Signals().OnActionCopy();
}

void C_UiMainWindow::on_ActionCut_triggered()
{
    if( ! ( Document().Context().Records().Flags() & FLAG_ACTION_CUT ) )
        return;

    bool empty = Document()
                 .MainWindow()
                 .RecordStructView()
                 .Selection()
                 .empty();

    if( empty )
        return;

    Document().Signals().OnActionCut();
}

void C_UiMainWindow::on_ActionPaste_triggered()
{
    if( !( Document().Context().Records().Flags() & FLAG_ACTION_PASTE ) )
        return;


    if( Document().Clipboard().CopyList().empty() )
        return;

    int position = -1;

    if ( !Document().MainWindow().RecordStructView().Selection().empty() )
    {
        auto front = Document().MainWindow().RecordStructView().Selection().front();
        int count = 0;

        for( auto record : Document().Context().Records() )
        {
            if( record == front )
            {
                position = count;
                break;
            }

            ++count;
        }
    }

    Document().Signals().EventData().clear();
    Document().Signals().EventData() << QString::number( position );
    Document().Signals().OnActionPaste();
}

void C_UiMainWindow::on_ActionRemove_triggered()
{
    if( !( Document().Context().Records().Flags() & FLAG_ACTION_REMOVE ) )
        return;

    list<C_Record*> selection_list = Document()
                                     .MainWindow()
                                     .RecordStructView()
                                     .Selection();

    if( selection_list.empty() )
        return;

    Document().Signals().OnActionRemove();
}

void C_UiMainWindow::on_ActionAdd_to_scene_triggered()
{
    if( !( Document().Context().Records().Flags() & FLAG_ACTION_ADD_SCENE ) )
        return;

    list<C_Record*> selection_list = Document()
                                     .MainWindow()
                                     .RecordStructView()
                                     .Selection();

    if( selection_list.empty() )
        return;

    Document().Signals().OnActionAddSceneItem();
}

void C_UiMainWindow::on_ActionAdd_triggered()
{
    int position = -1;

    if ( !Document().MainWindow().RecordStructView().Selection().empty() )
    {
        auto front = Document().MainWindow().RecordStructView().Selection().front();
        int count = 0;

        for( auto record : Document().Context().Records() )
        {
            if( record == front )
            {
                position = count;
                break;
            }

            ++count;
        }
    }

    Document().Signals().EventData().clear();
    Document().Signals().EventData() << QString::number( position );
    Document().Signals().OnActionAdd();
}

void C_UiMainWindow::on_ActionFind_triggered()
{
    QWidget* dialog = new C_UiFindRecord( Document(), this );
    dialog->show();
}

void C_UiMainWindow::on_ActionExit_triggered()
{
    close();
}

void C_UiMainWindow::on_ActionRun_triggered()
{
    ui->WebView->setHtml( "<html><body></body></html>" );
    ui->WebView->page()->mainFrame()->evaluateJavaScript(
        Document().Script().StringList().join( "" ) );
    ui->WebView->show();
}





