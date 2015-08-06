#include "FW/document.h"
#include "FW/UI/ui_main_window.h"

#include <QFileDialog>

C_Signals::C_Signals(C_Document& document, C_UiMainWindow& main_window, QObject* parent)
    :QObject(parent)
{
    m_Document = &document;
    m_MainWindow = &main_window;
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

void C_Signals::OnActionDocumentLoad()
{
    QString file_name = QFileDialog::getOpenFileName(&MainWindow(),
                                                     tr("Load File"),
                                                     "",
                                                     tr("JS Blocks Files (*.blk)"));
    if(file_name.isEmpty())
        return;

    QFile file(file_name);
    Document().FileLoad(file);

}

void C_Signals::OnActionDocumentSave()
{
    QString file_name = QFileDialog::getSaveFileName(&MainWindow(),
                                                     tr("Save File"),
                                                     tr("untitled.blk"),
                                                     tr("JS Blocks Files (*.blk)"));

    if(file_name.isEmpty())
        return;

    QFile file(file_name);
    Document().FileSave(file);
}

void C_Signals::OnActionSQLDocumentLoad()
{
    QString file_name = QFileDialog::getOpenFileName(&MainWindow(),
                                                     tr("Load SQL Database File"),
                                                     "",
                                                     tr("SQL Files (*.sql)"));

    if(file_name.isEmpty())
        return;

    Document().DatabaseLoad(file_name);
}

void C_Signals::OnActionSQLDocumentSave()
{
    QString file_name = QFileDialog::getSaveFileName(&MainWindow(),
                                                     tr("Save SQL Database File"),
                                                     tr("untitled.sql"),
                                                     tr("SQL Files (*.sql)"));

    if(file_name.isEmpty())
        return;

    Document().DatabaseSave(file_name);
}

void C_Signals::ConnectSignals()
{

    connect(
                this,
                C_Signals::RecordsChanged,
                this,
                C_Signals::OnRecordsChanged);

    connect(
                this,
                C_Signals::SceneChanged,
                this,
                C_Signals::OnSceneChanged);

    connect(
                this,
                C_Signals::ScriptChanged,
                this,
                C_Signals::OnScriptChanged);
}




