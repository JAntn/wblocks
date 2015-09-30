#include "FW/BK/html_block_stream.h"
#include "FW/RC/record.h"
#include "FW/BK/html_builder.h"
#include "FW/RC/struct.h"
#include "FW/BK/html_block.h"
#include "FW/tools.h"


TypeHtmlBuilder::TypeHtmlBuilder( TypeVariant* parent ):
    TypeVariant( parent ), m_BlockStream( 0 )
{
    // void
}

TypeHtmlBuilder::~TypeHtmlBuilder()
{
    // void
}

void TypeHtmlBuilder::Build( TypeStruct& root )
{
    if( m_BlockStream != 0 )
        delete m_BlockStream;

    m_BlockStream = new TypeHtmlBlockStream( this );

    BlockStream().Append( "\n<!DOCTYPE html>", "" );
    BlockStream().Append( "\n<html>", "" );
    BlockStream().Append( "\n<head>", "" );
    BlockStream().Append( "\n<style>", "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Html( BlockStream(), FLAG_ROLE_CSS, root );

    BlockStream().Append( "\n</style>", "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Html( BlockStream(), FLAG_ROLE_HEAD, root );

    BlockStream().Append( "\n</head>", "" );
    BlockStream().Append( "\n<body>", "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Html( BlockStream(), FLAG_ROLE_BODY, root );

    BlockStream().Append( "\n</body>", "" );
    BlockStream().Append( "\n<script>", "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Html( BlockStream(), FLAG_ROLE_JAVASCRIPT, root );

    BlockStream().Append( "\n</script>", "" );
    BlockStream().Append( "\n</html>", "" );
}

QString TypeHtmlBuilder::Text()
{
    QStringList html;

    for( TypeVariantPtr<TypeHtmlBlock> block : BlockStream() )
        html << block->Text();

    return html.join( "" );
}

QString TypeHtmlBuilder::FormattedText()
{

    QString html_block        = "<span style=\"background-color:White\">";
    QString html_not_editable = "<span style=\"background-color:#E6E6E6\">";
    QString html_selected     = "<span style=\"background-color:#C8FE2E\">";
    QString html_end          = "</span>";
    QStringList html;

    for( TypeVariantPtr<TypeHtmlBlock> block : BlockStream() )
    {
        QString text = block->Text();
        text = text.toHtmlEscaped();
        text = text.replace( "\n", "<br>" );
        text = text.replace( "\t", "&nbsp;&nbsp;&nbsp;&nbsp;" );
        text = text.replace( " ", "&nbsp;" );

        if( block->RecordId().isEmpty() )
            html << html_not_editable << text << html_end;
        else if( block->Selected() )
            html << html_selected << text << html_end;
        else if( !block->Selected() )
            html << html_block << text << html_end;
    }

    return html.join( "" );
}



