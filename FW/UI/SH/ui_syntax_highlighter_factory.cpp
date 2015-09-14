#include "FW/UI/SH/ui_syntax_highlighter_factory.h"

TypeUiSyntaxHighlighterFactory::TypeUiSyntaxHighlighterFactory( TypeVariant* parent ):
    TypeVariant( parent )
{
    // void
}

TypeUiSyntaxHighlighter* TypeUiSyntaxHighlighterFactory::NewInstance( QString format )
{
    QString file_name = m_FormatMap.value( format, "" );

    if( !file_name.isEmpty() )
        return new TypeUiSyntaxHighlighter( file_name );

    return 0;
}

void TypeUiSyntaxHighlighterFactory::AppendFormat( QString format, QString file_name )
{
    m_FormatMap.insert( format, file_name );
}

bool TypeUiSyntaxHighlighterFactory::Empty()
{
    return m_FormatMap.empty();
}

