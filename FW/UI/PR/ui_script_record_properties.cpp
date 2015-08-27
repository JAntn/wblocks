#include "FW/RC/script_record.h"
#include "FW/UI/PR/ui_script_record_properties.h"
#include "FW/document.h"
#include "FW/UI/ui_record_value_editor.h"
#include "ui_scriptrecordproperties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_text_editor_container.h"


C_UiScriptRecordProperties::C_UiScriptRecordProperties( C_ScriptRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiScriptRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->PlainTextEdit->setPlainText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiScriptRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiScriptRecordProperties::OnRemoveButtonClicked
    );
}

C_UiScriptRecordProperties::~C_UiScriptRecordProperties()
{
    delete ui;
}

void C_UiScriptRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->PlainTextEdit->toPlainText() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiScriptRecordProperties::OnRemoveButtonClicked()
{
    if( C_Document::AcceptMessage( tr( "Remove Record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}



