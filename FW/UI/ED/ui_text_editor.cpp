#include "ui_texteditor.h"
#include "FW/UI/ED/ui_text_editor.h"
#include <QFileDialog>


TypeUiTextEditor::TypeUiTextEditor( QString id, QString name, QString tab_name, TypeUiEditor::save_callback_t on_save_state, QWidget* parent ):
    TypeUiEditor( id, name, tab_name, on_save_state, parent ),
    ui( new Ui::TypeUiTextEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( m_Name );

    connect(
        ui->PlainTextEdit,
        QPlainTextEdit::textChanged,
        this,
        TypeUiTextEditor::OnTextChanged
    );
}

TypeUiTextEditor::~TypeUiTextEditor()
{
    delete ui;
}

void TypeUiTextEditor::SetText( QString text , bool signal_block )
{
    // WARNIG - BLOCKING SIGNALS

    if( signal_block )
    {
        QSignalBlocker blocker( ui->PlainTextEdit );
        ui->PlainTextEdit->setPlainText( text );
        return;
    }

    ui->PlainTextEdit->setPlainText( text );
}

QString TypeUiTextEditor::Text()
{
    return ui->PlainTextEdit->toPlainText();
}

void TypeUiTextEditor::OnTextChanged()
{
    if( !HasChanged() )
    {
        SetHasChanged( true );
        ui->NameLineEdit->setText( Name() + "*" );
    }
}
