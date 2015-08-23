#include "FW/RC/struct_record.h"
#include "FW/document.h"
#include "FW/UI/ui_struct_editor.h"
#include "ui_structeditor.h"

C_UiStructEditor::C_UiStructEditor( C_StructRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiStructEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiStructEditor::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiStructEditor::OnRemoveButtonClicked
    );
}

C_UiStructEditor::~C_UiStructEditor()
{
    delete ui;
}

void C_UiStructEditor::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().m_Name = ui->NameLineEdit->text();
    emit Document().Events().RecordsChanged();
}


void C_UiStructEditor::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}
