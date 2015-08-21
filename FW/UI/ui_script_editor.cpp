#include "FW/document.h"
#include "FW/RC/script_record.h"
#include "FW/UI/ui_script_editor.h"
#include "ui_scripteditor.h"
#include "FW/UI/ui_main_window.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "FW/RC/bool_record.h"
#include "FW/RC/string_record.h"
#include <QDebug>
#include <QDesktopWidget>
#include "FW/RC/file_record.h"
#include "FW/UI/ui_code_editor_container.h"

C_UiScriptEditor::C_UiScriptEditor( C_ScriptRecord& record, C_Document& document, QWidget* parent ) :
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiScriptEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->FileLineEdit->setText( Record().File().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiScriptEditor::OnButtonBoxAccepted
    );

    connect(
        ui->SelectButton,
        QPushButton::clicked,
        this,
        C_UiScriptEditor::OnSelectButtonClicked
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiScriptEditor::OnRemoveButtonClicked
    );
}

C_UiScriptEditor::~C_UiScriptEditor()
{
    delete ui;
}

void C_UiScriptEditor::OnButtonBoxAccepted()
{
    QString script_name = ui->NameLineEdit->text();

    if( !script_name.contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().m_Name = ui->NameLineEdit->text();

    QString file_name = ui->FileLineEdit->text();
    Record().File().SetValue( file_name );
    QString text = C_Document::LoadTextFile( file_name );
    Record().Code().SetValue( text );
    emit Document().Events().RecordsChanged();
}

void C_UiScriptEditor::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage(
                tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}

void C_UiScriptEditor::OnSelectButtonClicked()
{
    Record().File().ShowEditor( Document() );
    ui->FileLineEdit->setText( Record().File().Value() );
}
