#include "FW/document.h"
#include "FW/RC/script_file_record.h"
#include "FW/UI/ui_script_file_record_properties.h"
#include "FW/RC/file_record.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/RC/bool_record.h"
#include "FW/RC/string_record.h"
#include "FW/UI/ui_main_window.h"
#include "ui_scriptfilerecordproperties.h"
#include "ui_file_text_editor.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QDesktopWidget>


C_UiScriptFileRecordProperties::C_UiScriptFileRecordProperties( C_ScriptFileRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiScriptFileRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->FileLineEdit->setText( Record().File().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiScriptFileRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->SelectButton,
        QPushButton::clicked,
        this,
        C_UiScriptFileRecordProperties::OnSelectButtonClicked
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiScriptFileRecordProperties::OnRemoveButtonClicked
    );
}

C_UiScriptFileRecordProperties::~C_UiScriptFileRecordProperties()
{
    delete ui;
}

void C_UiScriptFileRecordProperties::OnButtonBoxAccepted()
{
    QString script_name = ui->NameLineEdit->text();

    if( !script_name.contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetName( ui->NameLineEdit->text() );
    Record().File().SetValue( ui->FileLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiScriptFileRecordProperties::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}

void C_UiScriptFileRecordProperties::OnSelectButtonClicked()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &Document().MainWindow(), QFileDialog::tr( "Select file" ), Record().File().FileFullName() );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Record().File().SetValue( file_name );
    ui->FileLineEdit->setText( file_name );
}
