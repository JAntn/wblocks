#include "FW/RC/struct_record.h"
#include "FW/document.h"
#include "FW/UI/PR/ui_struct_record_properties.h"
#include "ui_structrecordproperties.h"

C_UiStructRecordProperties::C_UiStructRecordProperties( C_StructRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiStructRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiStructRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiStructRecordProperties::OnRemoveButtonClicked
    );
}

C_UiStructRecordProperties::~C_UiStructRecordProperties()
{
    delete ui;
}

void C_UiStructRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}


void C_UiStructRecordProperties::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage( tr( "Remove Record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}
