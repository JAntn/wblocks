#include "FW/RC/string_record.h"
#include "FW/UI/ui_string_record_properties.h"
#include "FW/document.h"
#include "FW/UI/ui_record_value_editor.h"
#include "ui_stringrecordproperties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_text_editor_container.h"


C_UiStringRecordProperties::C_UiStringRecordProperties( C_StringRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiStringRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->PlainTextEdit->setPlainText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiStringRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiStringRecordProperties::OnRemoveButtonClicked
    );
}

C_UiStringRecordProperties::~C_UiStringRecordProperties()
{
    delete ui;
}

void C_UiStringRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->PlainTextEdit->toPlainText() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiStringRecordProperties::OnRemoveButtonClicked()
{
    if( C_Document::AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}



