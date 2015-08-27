#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/UI/PR/ui_record_properties.h"
#include "ui_recordproperties.h"

C_UiRecordProperties::C_UiRecordProperties( C_Record& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ValueLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiRecordProperties::OnRemoveButtonClicked
    );
}

C_UiRecordProperties::~C_UiRecordProperties()
{
    delete ui;
}

void C_UiRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->ValueLineEdit->text() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiRecordProperties::OnRemoveButtonClicked()
{
    if( Document().AcceptMessage( tr( "Remove Record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}


