#include "FW/RC/string_record.h"
#include "FW/UI/ui_string_editor.h"
#include "FW/document.h"
#include "ui_stringeditor.h"


C_UiStringEditor::C_UiStringEditor( C_StringRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiStringEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->TextEdit->setPlainText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiStringEditor::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiStringEditor::OnRemoveButtonClicked
    );
}

C_UiStringEditor::~C_UiStringEditor()
{
    delete ui;
}

void C_UiStringEditor::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().m_Value = ui->TextEdit->toPlainText();
    Record().m_Name = ui->NameLineEdit->text();
    emit Document().Events().RecordsChanged();
}

void C_UiStringEditor::OnRemoveButtonClicked()
{
    if( C_Document::AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}



