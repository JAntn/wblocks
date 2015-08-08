#include "FW/UI/ui_struct_editor.h"

#include "ui_structeditor.h"

#include <FW/RC/struct_record.h>

#include <FW/document.h>

C_UiStructEditor::C_UiStructEditor(C_StructRecord& record, C_Document& document, QWidget *parent) :
    QDialog(parent),
    m_Record(&record),
    m_Document(&document),
    ui(new Ui::C_UiStructEditor)
{
    ui->setupUi(this);
    ui->NameLineEdit->setText(Record().Name());
}

C_UiStructEditor::~C_UiStructEditor()
{
    delete ui;
}

void C_UiStructEditor::on_ButtonBox_accepted()
{
    if(!ui->NameLineEdit->text().contains(QRegExp("^\\S+$"))) {
        Document().Message(tr("Name must not contain white spaces"));
        return;
    }

    Record().m_Name = ui->NameLineEdit->text();

    emit Document()
            .Signals()
            .RecordsChanged();
}
