#include "FW/document.h"
#include "FW/RC/script_record.h"

#include "FW/UI/ui_script_editor.h"
#include "ui_scripteditor.h"
#include "FW/UI/ui_main_window.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "FW/RC/bool_record.h"
#include "FW/RC/string_record.h"
#include <QDebug>



C_UiScriptEditor::C_UiScriptEditor(C_ScriptRecord& record, C_Document& document, QWidget* parent) :
    QDialog(parent),
    m_Record(&record),
    m_Document(&document),
    ui(new Ui::C_UiScriptEditor)
{
    ui->setupUi(this);

    ui->NameLineEdit->setText(Record().Name());

    if( Record().IsFromFile().Value() == "False" )
    {
        ui->FileCheckBox->setChecked(false);
        ui->FileLineEdit->setEnabled(false);
        ui->SaveButton->setEnabled(false);
        ui->LoadButton->setEnabled(false);
        ui->PlainTextEdit->setPlainText(Record().Code().Value());
    }
    else {
        ui->FileCheckBox->setChecked(true);
        ui->FileLineEdit->setEnabled(true);
        ui->SaveButton->setEnabled(true);
        ui->LoadButton->setEnabled(true);

        ui->FileLineEdit->setText(Record().FileName().Value());

        QString text = C_Document::LoadTextFile(Record().FileName().Value());
        ui->PlainTextEdit->setPlainText(text);
    }


}

C_UiScriptEditor::~C_UiScriptEditor()
{
    delete ui;
}

void C_UiScriptEditor::on_ButtonBox_accepted()
{
    if(!ui->NameLineEdit->text().contains(QRegExp("^\\S+$"))) {
        Document().Message(tr("Name must not contain white spaces"));
        return;
    }

    Record().m_Name = ui->NameLineEdit->text();

    if(ui->FileCheckBox->isChecked())
    {
        Record().IsFromFile().SetValue("True");
        Record().FileName().SetValue(ui->FileLineEdit->text());

        QString text = C_Document::LoadTextFile(ui->FileLineEdit->text());
        Record().Code().SetValue(text);
    }
    else
    {
        Record().IsFromFile().SetValue("False");
        Record().FileName().SetValue("");
        Record().Code().SetValue(ui->PlainTextEdit->toPlainText());
    }

    emit Document()
            .Signals()
            .RecordsChanged();
}

void C_UiScriptEditor::on_RemoveButton_clicked()
{
    if(  Document().AcceptMessage(
                tr("Do you want to remove this record?")))
    {
        delete & Record();

        emit Document()
                .Signals()
                .RecordsChanged();

        close();
    }
}

#include <QDebug>

void C_UiScriptEditor::on_LoadButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(&Document().MainWindow(),
                                                     tr("Load File"),
                                                     Record().FileName().Value(),
                                                     tr("JS Files (*.js)"));
    if(file_name.isEmpty())
        return;

    ui->FileLineEdit->setText(file_name);

    QString text = C_Document::LoadTextFile(file_name);
    ui->PlainTextEdit->setPlainText(text);
}

void C_UiScriptEditor::on_SaveButton_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(&Document().MainWindow(),
                                                     tr("Save File"),
                                                     Record().FileName().Value(),
                                                     tr("JS Files (*.js)"));

    if(file_name.isEmpty())
        return;

    ui->FileLineEdit->setText(file_name);

    C_Document::SaveTextFile(file_name,ui->PlainTextEdit->toPlainText());


}

void C_UiScriptEditor::on_FileCheckBox_stateChanged(int arg1)
{
    if(ui->FileCheckBox->isChecked())
    {
        ui->FileLineEdit->setEnabled(true);
        ui->SaveButton->setEnabled(true);
        ui->LoadButton->setEnabled(true);

        return;
    }

    ui->FileLineEdit->setEnabled(false);
    ui->SaveButton->setEnabled(false);
    ui->LoadButton->setEnabled(false);
}
