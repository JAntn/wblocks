#include "FW/RC/bool_record.h"
#include "FW/document.h"

#include "FW/UI/ui_bool_editor.h"
#include "ui_booleditor.h"


C_UiBoolEditor::C_UiBoolEditor(C_BoolRecord& record, C_Document& document, QWidget* parent) :
    QDialog(parent),
    m_Record(&record),
    m_Document(&document),
    ui(new Ui::C_UiBoolEditor)
{
    ui->setupUi(this);
    ui->NameLineEdit->setText(Record().Name());

    ui->ComboBox->addItem("False");
    ui->ComboBox->addItem("True");

    int index = 0;
    if( Record().Value() == "True") {
            index = 1;
    }

    ui->ComboBox->setCurrentIndex(index);
}

C_UiBoolEditor::~C_UiBoolEditor()
{
    delete ui;
}

void C_UiBoolEditor::on_ButtonBox_accepted()
{
    if(!ui->NameLineEdit->text().contains(QRegExp("^\\S+$"))) {
        Document().Message(tr("Name must not contain white spaces"));
        return;
    }

    m_Record->m_Value = ui->ComboBox->currentText();
    m_Record->m_Name = ui->NameLineEdit->text();


    emit Document()
            .Signals()
            .RecordsChanged();
}

void C_UiBoolEditor::on_RemoveButton_clicked()
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


