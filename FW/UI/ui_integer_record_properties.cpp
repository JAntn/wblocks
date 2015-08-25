#include "FW/RC/integer_record.h"
#include "FW/document.h"
#include "FW/UI/ui_integer_record_properties.h"
#include "ui_integerrecordproperties.h"
#include <QRegExp>

C_UiIntegerRecordProperties::C_UiIntegerRecordProperties( C_IntegerRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiIntegerRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ValueLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiIntegerRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiIntegerRecordProperties::OnRemoveButtonClicked
    );
}

C_UiIntegerRecordProperties::~C_UiIntegerRecordProperties()
{
    delete ui;
}

void C_UiIntegerRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    if( !ui->ValueLineEdit->text().contains( QRegExp( "(^\\s*[-+]?\\d+(E[+]?\\d+)?\\s*$)" ) ) )
    {
        Document().Message( tr( "Bad number string" ) );
        return;
    }

    Record().SetValue( ui->ValueLineEdit->text() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiIntegerRecordProperties::OnRemoveButtonClicked()
{
    if( C_Document::AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}



