#include "FW/RC/real_record.h"
#include "FW/document.h"
#include "FW/UI/ui_real_record_properties.h"
#include "ui_realrecordproperties.h"

C_UiRealRecordProperties::C_UiRealRecordProperties( C_RealRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiRealRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ValueLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiRealRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiRealRecordProperties::OnRemoveButtonClicked
    );
}

C_UiRealRecordProperties::~C_UiRealRecordProperties()
{
    delete ui;
}

void C_UiRealRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    if( !ui->ValueLineEdit->text().contains( QRegExp( "(^\\s*[-+]?\\d+(.\\d+)?([Ee][+-]?\\d+(.\\d+)?)?\\s*$)" ) ) )
    {
        Document().Message( tr( "Bad real number string" ) );
        return;
    }

    Record().SetValue( ui->ValueLineEdit->text() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiRealRecordProperties::OnRemoveButtonClicked()
{
    if( Document().AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}


