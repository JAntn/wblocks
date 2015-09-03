#include "FW/UI/ED/ui_text_editor.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "ui_texteditor.h"


TypeUiTextEditor::TypeUiTextEditor( QString id, QString name, QString tab_name,
                                    QWidget* parent ,
                                    TypeUiEditor::TypeSaveCallback save_callback,
                                    TypeUiSyntaxHighlighter* syntax_higlighter ) :
    TypeUiEditor( id, name, tab_name, parent, save_callback ),
    m_SyntaxHighlighter( syntax_higlighter ),
    ui( new Ui::TypeUiTextEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( m_Name );

    connect(
        ui->TextEdit,
        QTextEdit::textChanged,
        this,
        TypeUiTextEditor::OnTextChanged
    );

    QFont font;
    font.setFamily( "Courier" );
    font.setFixedPitch( true );
    font.setPointSize( 9 );
    setFont( font );

    if( m_SyntaxHighlighter != 0 )
        m_SyntaxHighlighter->setDocument( ui->TextEdit->document() );
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
        QSignalBlocker blocker( ui->TextEdit );
        ui->TextEdit->setPlainText( text );
        return;
    }

    ui->TextEdit->setPlainText( text );
}

void TypeUiTextEditor::SetSyntaxHighlighter( TypeUiSyntaxHighlighter* syntax_higlighter )
{
    m_SyntaxHighlighter = syntax_higlighter;

    if( m_SyntaxHighlighter != 0 )
        m_SyntaxHighlighter->setDocument( ui->TextEdit->document() );
}

QTextEdit& TypeUiTextEditor::TextEditWidget()
{
    return *ui->TextEdit;
}

QLineEdit&TypeUiTextEditor::NameLineEditWidget()
{
    return *ui->NameLineEdit;
}

QString TypeUiTextEditor::Text()
{
    return ui->TextEdit->toPlainText();
}

void TypeUiTextEditor::OnTextChanged()
{
    if( !HasChanged() )
    {
        SetHasChanged( true );
        ui->NameLineEdit->setText( Name() + "*" );
    }
}
