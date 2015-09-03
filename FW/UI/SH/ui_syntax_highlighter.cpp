#include "FW/controller.h"
#include "ui_syntax_highlighter.h"

TypeUiSyntaxHighlighter::TypeUiSyntaxHighlighter( QString rules_file , TypeVariant* variant , QTextDocument* parent )
    : QSyntaxHighlighter( parent ), TypeVariant( variant )
{
    QFont::Weight font_weight[] = { QFont::Normal, QFont::Bold };
    bool font_italic[] = { false, true };
    QString rules_file_txt = TypeController::LoadTextFile( rules_file );
    QStringList rule_list = rules_file_txt.split( "@", QString::SkipEmptyParts );

    for( QString rule : rule_list )
    {
        QStringList   rule_tokens = rule.split( "\n", QString::SkipEmptyParts );
        QStringList   format_tokens = rule_tokens[0].split( "," );
        QString       name  = format_tokens[0];

        bool uglyok;
        QColor        color  = QRgb( format_tokens[1].split( "#" ).back().toUInt( &uglyok, 16 ) );
        QFont::Weight weight = font_weight[format_tokens[2].toUInt()];
        bool          italic  = font_italic[format_tokens[3].toUInt()];

        QTextCharFormat text_format;
        text_format.setForeground( QBrush( color ) );
        text_format.setFontWeight( weight );
        text_format.setFontItalic( italic );

        TypeHighlightingRule highligth_rule;
        highligth_rule.format = text_format;
        highligth_rule.name = name;
        rule_tokens.pop_front();
        highligth_rule.tokens = rule_tokens;


        if( name.startsWith( "[multcomment]" ) )
            m_CommentHighlightingRules.append( highligth_rule );
        else
            m_HighlightingRules.append( highligth_rule );
    }
}

void TypeUiSyntaxHighlighter::highlightBlock( const QString& text )
{
    for ( TypeHighlightingRule& rule : m_HighlightingRules )
    {
        for( QString token : rule.tokens  )
        {
            QRegExp expression( token );
            int index = expression.indexIn( text );

            while ( index >= 0 )
            {
                int length = expression.matchedLength();
                setFormat( index, length, rule.format );
                index = expression.indexIn( text, index + length );
            }
        }
    }

    for( TypeHighlightingRule& rule : m_CommentHighlightingRules )
    {
        QRegExp comment_start( rule.tokens[0] );
        QRegExp comment_end( rule.tokens[1] );

        setCurrentBlockState( 0 );

        int start_index = 0;

        if ( previousBlockState() != 1 )
            start_index = comment_start.indexIn( text );

        while ( start_index >= 0 )
        {
            int end_index = comment_end.indexIn( text, start_index );
            int comment_length;

            if ( end_index == -1 )
            {
                setCurrentBlockState( 1 );
                comment_length = text.length() - start_index;
            }
            else
            {
                comment_length = end_index - start_index
                                 + comment_end.matchedLength();
            }

            setFormat( start_index, comment_length, rule.format );
            start_index = comment_start.indexIn( text, start_index + comment_length );
        }
    }
}
