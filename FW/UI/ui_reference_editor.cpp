#include "FW/RC/reference_record.h"
#include "FW/document.h"
#include "FW/UI/ui_reference_editor.h"
#include "ui_referenceeditor.h"

C_UiReferenceEditor::C_UiReferenceEditor( C_ReferenceRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiReferenceEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ReferenceLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiReferenceEditor::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiReferenceEditor::OnRemoveButtonClicked
    );

    connect(
        ui->EditButton,
        QPushButton::clicked,
        this,
        C_UiReferenceEditor::OnEditButtonClicked
    );

    connect(
        ui->ReferenceLineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiReferenceEditor::OnReferenceLineEditReturnPressed
    );
}

C_UiReferenceEditor::~C_UiReferenceEditor()
{
    delete ui;
}

void C_UiReferenceEditor::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    if( !ui->ReferenceLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Reference must not contain white spaces" ) );
        return;
    }

    m_Record->SetDocument( Document() );
    m_Record->SetValue( ui->ReferenceLineEdit->text() );
    m_Record->SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiReferenceEditor::OnRemoveButtonClicked()
{
    if(  Document().AcceptMessage(
                tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document()
        .Events()
        .RecordsChanged();
        close();
    }
}

void C_UiReferenceEditor::OnEditButtonClicked()
{
    C_Record* record = Document().Records().FromId( m_Record->m_Value );

    if( record != 0 )
        record->ShowEditor( Document() );
}

void C_UiReferenceEditor::OnReferenceLineEditReturnPressed()
{

    if( !ui->ReferenceLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Reference must not contain white spaces" ) );
        return;
    }

    m_Record->SetValue( ui->ReferenceLineEdit->text() );
}
