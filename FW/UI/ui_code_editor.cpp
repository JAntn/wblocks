#include "FW/UI/ui_code_editor.h"
#include "ui_codeeditor.h"
#include <QFileDialog>
#include "FW/document.h"

C_UiCodeEditor::C_UiCodeEditor( QString file_name, QWidget* parent ) :
    m_FileName( file_name ),
    m_HasChanged( false ),
    QWidget( parent ),
    ui( new Ui::C_UiCodeEditor )
{
    ui->setupUi( this );
    ui->FileLineEdit->setText( file_name );
    ui->PlainTextEdit->setPlainText( C_Document::LoadTextFile( file_name ) );

    connect(
        ui->PlainTextEdit,
        QPlainTextEdit::textChanged,
        this,
        C_UiCodeEditor::OnTextChanged
    );
}

C_UiCodeEditor::~C_UiCodeEditor()
{
    Save();
    delete ui;
}

void C_UiCodeEditor::OnTextChanged()
{
    if( !HasChanged() )
    {
        SetHasChanged( true );
        ui->FileLineEdit->setText( FileName() + "*" );

        emit TextChangedEvent();
    }
}

void C_UiCodeEditor::Save()
{
    C_Document::SaveTextFile( FileName(), ui->PlainTextEdit->toPlainText() );

    SetHasChanged( false );
    ui->FileLineEdit->setText( FileName() );

    emit SavedEvent();
}
