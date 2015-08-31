#include "FW/RC/HTML/html_record.h"
#include "FW/UI/PR/ui_html_record_properties.h"
#include "FW/document.h"
#include "ui_htmlrecordproperties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_editor_container.h"


TypeUiHtmlRecordProperties::TypeUiHtmlRecordProperties( TypeHtmlRecord& record, TypeDocument& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::TypeUiHtmlRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->PlainTextEdit->setPlainText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        TypeUiHtmlRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        TypeUiHtmlRecordProperties::OnRemoveButtonClicked
    );
}

TypeUiHtmlRecordProperties::~TypeUiHtmlRecordProperties()
{
    delete ui;
}

void TypeUiHtmlRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        TypeController::Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->PlainTextEdit->toPlainText() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Controller().RecordsChanged();
}

void TypeUiHtmlRecordProperties::OnRemoveButtonClicked()
{
    if( TypeController::AcceptMessage( tr( "Remove Record?" ) ) )
    {
        delete & Record();
        emit Document().Controller().RecordsChanged();
        close();
    }
}



