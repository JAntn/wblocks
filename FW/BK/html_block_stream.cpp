#include "FW/BK/html_block_stream.h"
#include "FW/BK/html_block.h"

TypeHtmlBlockStream::TypeHtmlBlockStream( TypeVariant* parent ):
    TypeVariantStruct( parent ), m_Count( 0 )
{
    // void
}

void TypeHtmlBlockStream::Append( QString text, QString record_id )
{
    //
    // Create a new block from text input:

    TypeVariant* block = new TypeHtmlBlock( m_Count, text, record_id );
    this->TypeVariantStruct::Append( *block );
    m_Count += text.size();
}

TypeHtmlBlock* TypeHtmlBlockStream::BlockFromCursorPosition( int cursor_position )
{
    int position  = 0;
    TypeVariantPtr<TypeHtmlBlock> prev_block = *begin();

    for( TypeVariantPtr<TypeHtmlBlock> block : *this )
    {
        position = block->Position();

        if( position > cursor_position )
            return prev_block;

        prev_block = block;
    }

    if( position + prev_block->Text().size() < cursor_position )
        return prev_block;

    return 0;
}

TypeHtmlBlock* TypeHtmlBlockStream::BlockFromRecordId( QString id )
{
    for( TypeVariantPtr<TypeHtmlBlock> block : *this )
    {
        if( block->RecordId() == id )
            return block;
    }

    return 0;
}
