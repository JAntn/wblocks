#include "FW/RC/HTML/html_record.h"
#include "FW/UI/PR/ui_html_record_properties.h"
#include "FW/document.h"
#include "ui_htmlrecordproperties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_editor_container.h"


C_UiHtmlRecordProperties::C_UiHtmlRecordProperties( C_HtmlRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiHtmlRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->PlainTextEdit->setPlainText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiHtmlRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiHtmlRecordProperties::OnRemoveButtonClicked
    );
}

C_UiHtmlRecordProperties::~C_UiHtmlRecordProperties()
{
    delete ui;
}

void C_UiHtmlRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Controller::Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->PlainTextEdit->toPlainText() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Controller().RecordsChanged();
}

void C_UiHtmlRecordProperties::OnRemoveButtonClicked()
{
    if( C_Controller::AcceptMessage( tr( "Remove Record?" ) ) )
    {
        delete & Record();
        emit Document().Controller().RecordsChanged();
        close();
    }
}



