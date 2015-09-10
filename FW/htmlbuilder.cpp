#include "FW/BK/html_block_stream.h"
#include "FW/RC/record.h"
#include "FW/htmlbuilder.h"
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

    BlockStream().Append(
        "\n<!DOCTYPE html>"
        "\n<html>",
        "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Html( BlockStream() );

    BlockStream().Append( "\n<script>", "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Script( BlockStream() );

    BlockStream().Append( "\n</script>", "" );

    BlockStream().Append( "\n</html>", "" );
}

QString TypeHtmlBuilder::Text()
{
    QStringList html;

    for( TypeVariantPtr<TypeHtmlBlock> block : BlockStream() )
    {
        html << block->Text();
    }

    return html.join( "" );
}

QString TypeHtmlBuilder::FormattedText()
{

    QString html_block = "<span style=\"background-color:White\">";
    QString html_not_editable = "<span style=\"background-color:WhiteSmoke\">";
    QString html_selected = "<span style=\"background-color:PaleGreen\">";
    QString html_end = "</span>";
    QStringList html;

    for( TypeVariantPtr<TypeHtmlBlock> block : BlockStream() )
    {

        QString text = block->Text();
        text = text.toHtmlEscaped();
        text = text.replace("\n","<br>");
        text = text.replace("\t","&nbsp;&nbsp;&nbsp;&nbsp;");
        text = text.replace(" ","&nbsp;");

        if( block->RecordId().isEmpty() )
            html << html_not_editable << text << html_end;
        else if( block->Selected() )
            html << html_selected << text << html_end;
        else if( !block->Selected() )
            html << html_block << text << html_end;
    }

    return html.join( "" );
}



