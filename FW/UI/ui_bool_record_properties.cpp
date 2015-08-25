#include "FW/document.h"
#include "FW/RC/bool_record.h"
#include "FW/UI/ui_bool_record_properties.h"
#include "ui_boolrecordproperties.h"


C_UiBoolRecordProperties::C_UiBoolRecordProperties( C_BoolRecord& record, C_Document& document, QWidget* parent ) :
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiBoolRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ComboBox->addItem( "False" );
    ui->ComboBox->addItem( "True" );

    int index = 0;

    if( Record().Value() == "True" )
        index = 1;

    ui->ComboBox->setCurrentIndex( index );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiBoolRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiBoolRecordProperties::OnRemoveButtonClicked
    );

}

C_UiBoolRecordProperties::~C_UiBoolRecordProperties()
{
    delete ui;
}

void C_UiBoolRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->ComboBox->currentText() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiBoolRecordProperties::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}


