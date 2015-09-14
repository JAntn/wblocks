#include "FW/UI/ED/ui_text_editor.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "ui_texteditor.h"


TypeUiTextEditor::TypeUiTextEditor(QString id, QString name, QString tab_name,
                                    QWidget* parent ,
                                    TypeUiEditor::TypeSaveCallback save_callback,
                                    TypeUiEditor::TypeSaveCallback save_as_callback,
                                    TypeUiSyntaxHighlighter* syntax_higlighter ) :
    TypeUiEditor( id, name, tab_name, parent, save_callback, save_as_callback ),
    m_SyntaxHighlighter( syntax_higlighter ),
    ui( new Ui::TypeUiTextEditor )
{
    m_ShowTitleAsterisc = true;

    ui->setupUi( this );

    connect(
        ui->TextEdit,
        QTextEdit::textChanged,
        this,
        TypeUiTextEditor::OnTextChanged
    );

    connect(
        this,
        TypeUiEditor::HasSaved,
        this,
        TypeUiTextEditor::OnTextSaved
    );

    QFont font;
    font.setFamily( "Courier" );
    font.setFixedPitch( true );
    font.setPointSize( 9 );
    setFont( font );

    if( m_SyntaxHighlighter != 0 )
        m_SyntaxHighlighter->setDocument( ui->TextEdit->document() );

    SetHasChanged( false );
    ui->NameLineEdit->setText( Name() );
}

TypeUiTextEditor::~TypeUiTextEditor()
{
    delete ui;
}

void TypeUiTextEditor::SetText( QString text )
{
    QSignalBlocker block( this );
    ui->TextEdit->setPlainText( text );
}

void TypeUiTextEditor::SetFormattedText( QString text )
{
    QSignalBlocker block( this );
    ui->TextEdit->setHtml( text );
}

void TypeUiTextEditor::SetSyntaxHighlighter( TypeUiSyntaxHighlighter* syntax_higlighter )
{
    m_SyntaxHighlighter = syntax_higlighter;

    if( m_SyntaxHighlighter != 0 )
        m_SyntaxHighlighter->setDocument( ui->TextEdit->document() );
}

void TypeUiTextEditor::UpdateTitle()
{
    if( HasChanged() )
        ui->NameLineEdit->setText( Name() + "*" );
    else
        ui->NameLineEdit->setText( Name() );
}

QString TypeUiTextEditor::Text()
{
    return ui->TextEdit->toPlainText();
}

void TypeUiTextEditor::OnTextChanged()
{
    SetHasChanged( true );

    if( ShowTitleAsterisc() )
        UpdateTitle();
}

void TypeUiTextEditor::OnTextSaved()
{
    SetHasChanged( false );
    UpdateTitle();
}

