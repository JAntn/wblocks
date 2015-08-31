#include "ui_texteditor.h"
#include "FW/UI/ED/ui_text_editor.h"
#include <QFileDialog>


C_UiTextEditor::C_UiTextEditor( QString id, QString name, QString tab_name, C_UiEditor::save_callback_t on_save_state, QWidget* parent ):
    C_UiEditor( id, name, tab_name, on_save_state, parent ),
    ui( new Ui::C_UiTextEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( m_Name );

    connect(
        ui->PlainTextEdit,
        QPlainTextEdit::textChanged,
        this,
        C_UiTextEditor::OnTextChanged
    );
}

C_UiTextEditor::~C_UiTextEditor()
{
    delete ui;
}

void C_UiTextEditor::SetText( QString text , bool signal_block )
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

QString C_UiTextEditor::Text()
{
    return ui->PlainTextEdit->toPlainText();
}

void C_UiTextEditor::OnTextChanged()
{
    if( !HasChanged() )
    {
        SetHasChanged( true );
        ui->NameLineEdit->setText( Name() + "*" );
    }
}
