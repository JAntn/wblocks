#include "FW/RC/real_record.h"
#include "FW/document.h"

#include "FW/UI/ui_real_editor.h"
#include "ui_realeditor.h"


C_UiRealEditor::C_UiRealEditor(C_RealRecord& record, C_Document& document, QWidget* parent) :
    QDialog(parent),
    m_Record(&record),
    m_Document(&document),
    ui(new Ui::C_UiRealEditor)
{
    ui->setupUi(this);
    ui->NameLineEdit->setText(Record().Name());
    ui->ValueLineEdit->setText(Record().Value());

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiRealEditor::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiRealEditor::OnRemoveButtonClicked
    );
}

C_UiRealEditor::~C_UiRealEditor()
{
    delete ui;
}
#include<QMessageBox>

void C_UiRealEditor::OnButtonBoxAccepted()
{
    if(!ui->NameLineEdit->text().contains(QRegExp("^\\S+$"))) {
        Document().Message(tr("Name must not contain white spaces"));
        return;
    }

    if(!ui->ValueLineEdit->text().contains(QRegExp("(^\\s*[-+]?\\d+(.\\d+)?([Ee][+-]?\\d+(.\\d+)?)?\\s*$)"))) {
        Document().Message(tr("Bad real number string"));
        return;
    }

    m_Record->m_Value = ui->ValueLineEdit->text();
    m_Record->m_Name = ui->NameLineEdit->text();

    emit Document()
            .Events()
            .RecordsChanged();
}

void C_UiRealEditor::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage(
                tr("Do you want to remove this record?")))
    {
        delete & Record();

        emit Document()
                .Events()
                .RecordsChanged();

        close();
    }
}


