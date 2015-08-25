#include "ui_texteditor.h"
#include "FW/UI/ui_text_editor.h"
#include "FW/document.h"
#include <QFileDialog>


C_UiTextEditor::C_UiTextEditor( QString id, QString name, QString tab_name, QWidget* parent ) :
    QWidget( parent ),
    m_Id( id ),
    m_Name( name ),
    m_TabName( tab_name ),
    m_HasChanged( false ),
    ui( new Ui::C_UiTextEditor )
{
    ui->setupUi( this );

    if( m_TabName.isEmpty() )
        m_TabName = m_Name;

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
