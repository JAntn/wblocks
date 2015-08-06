#include "FW/RC/record.h"

#include "FW/UI/ui_main_window.h"
#include "ui_mainwindow.h"

#include "FW/UI/ui_add_record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"

#include "FW/UI/ui_record_struct_view.h"
#include "FW/UI/ui_find_record.h"
#include "ui_findrecord.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QtWebKitWidgets>

C_UiMainWindow::C_UiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::C_UiMainWindow)
{
    ui->setupUi(this);  

    m_Document = new C_Document(*this);
    m_RecordStructView = new C_UiRecordStructView(Document(),this);

    ui->TableViewLayout->addWidget(m_RecordStructView);
    ui->GraphicsView->setScene(&Document().Context().Scene().GraphicsScene());

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

    for(QString str : Document().Script().StringList() ) {
        ui->TextEdit->append(str);
    }

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
                ui->ActionDocumentLoad,
                QAction::triggered,
                &Document().Signals(),
                C_Signals::OnActionDocumentLoad);

    connect(
                ui->ActionDocumentSave,
                QAction::triggered,
                &Document().Signals(),
                C_Signals::OnActionDocumentSave);

    connect(
                ui->ActionSQLDocumentLoad,
                QAction::triggered,
                &Document().Signals(),
                C_Signals::OnActionSQLDocumentLoad);

    connect(
                ui->ActionSQLDocumentSave,
                QAction::triggered,
                &Document().Signals(),
                C_Signals::OnActionSQLDocumentSave);
}

void C_UiMainWindow::on_ActionNew_triggered()
{
    Document().Clear();
}

void C_UiMainWindow::on_ActionAdd_triggered()
{
    QWidget* dialog = new C_UiAddRecord(Document(),-1,this);
    dialog->show();
}

void C_UiMainWindow::on_ActionFind_triggered()
{
    QWidget* dialog = new C_UiFindRecord(Document(),this);
    dialog->show();
}

void C_UiMainWindow::on_ActionExit_triggered()
{
    close();
}

void C_UiMainWindow::on_ActionRun_triggered()
{

    ui->WebView->setHtml("<html><body></body></html>");
    ui->WebView->page()->mainFrame()->evaluateJavaScript(
                Document().Script().StringList().join(""));
    ui->WebView->show();
}



