#include "FW/RC/string_record.h"
#include "FW/UI/ui_string_editor.h"
#include "ui_stringeditor.h"

#include <FW/document.h>

C_UiStringEditor::C_UiStringEditor(C_StringRecord& record, C_Document& document, QWidget* parent) :
    QDialog(parent),
    m_Record(&record),
    m_Document(&document),
    ui(new Ui::C_UiStringEditor)
{
    ui->setupUi(this);
    ui->NameLineEdit->setText(m_Record->m_Name);
    ui->TextEdit->setPlainText(m_Record->m_Value);
}

C_UiStringEditor::~C_UiStringEditor()
{
    delete ui;
}

void C_UiStringEditor::on_ButtonBox_accepted()
{
    if(!ui->NameLineEdit->text().contains(QRegExp("^\\S+$"))) {
        Document().Message(tr("Name must not contain white spaces"));
        return;
    }

    Record().m_Value = ui->TextEdit->toPlainText();
    Record().m_Name = ui->NameLineEdit->text();

    emit Document()
            .Signals()
            .RecordsChanged();
}

void C_UiStringEditor::on_RemoveButton_clicked()
{
    if( C_Document::AcceptMessage(
            tr("Do you want to remove this record?")))
    {
        delete & Record();

        emit Document()
                .Signals()
                .RecordsChanged();

        close();
    }
}



