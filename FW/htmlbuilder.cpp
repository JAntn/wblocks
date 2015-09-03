#include "FW/BK/block_stream.h"
#include "FW/RC/record.h"
#include "FW/htmlbuilder.h"
#include "FW/RC/record_struct.h"
#include "FW/BK/block.h"
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

void TypeHtmlBuilder::Build( TypeRecordStruct& root )
{
    if( m_BlockStream != 0 )
        delete m_BlockStream;

    m_BlockStream = new TypeBlockStream( this );

    BlockStream().Append(
        "\n<!DOCTYPE html>"
        "\n<html>"
        "\n<script>",
        "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Script( BlockStream() );

    BlockStream().Append( "\n</script>", "" );

    for( TypeVariantPtr<TypeRecord> record : root )
        record->Html( BlockStream() );

    BlockStream().Append( "\n</html>", "" );
}

QString TypeHtmlBuilder::Text()
{
    QStringList html;

    for( TypeVariantPtr<TypeBlock> block : BlockStream() )
        html << block->Text();

    return html.join( "" );
}



