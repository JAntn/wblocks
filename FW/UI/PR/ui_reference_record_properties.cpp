#include "FW/RC/reference_record.h"
#include "FW/document.h"
#include "FW/UI/PR/ui_reference_record_properties.h"
#include "ui_referencerecordproperties.h"

C_UiReferenceRecordProperties::C_UiReferenceRecordProperties( C_ReferenceRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiReferenceRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ReferenceLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiReferenceRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiReferenceRecordProperties::OnRemoveButtonClicked
    );

    connect(
        ui->ReferenceLineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiReferenceRecordProperties::OnReferenceLineEditReturnPressed
    );
}

C_UiReferenceRecordProperties::~C_UiReferenceRecordProperties()
{
    delete ui;
}

void C_UiReferenceRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    if( !ui->ReferenceLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Reference must not contain white spaces" ) );
        return;
    }

    Record().SetRoot( Document().Root() );
    Record().SetName( ui->NameLineEdit->text() );
    Record().SetValue( ui->ReferenceLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiReferenceRecordProperties::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage(
                tr( "Remove Record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}


void C_UiReferenceRecordProperties::OnReferenceLineEditReturnPressed()
{
    if( !ui->ReferenceLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Reference must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->ReferenceLineEdit->text() );
}
