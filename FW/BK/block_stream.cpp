#include "FW/BK/block_stream.h"
#include "FW/BK/block.h"

TypeBlockStream::TypeBlockStream( TypeVariant* parent ):
    TypeVariantStruct( parent ), m_Count( 0 )
{
    // void
}

void TypeBlockStream::Append( QString text, QString record_id )
{
    TypeVariant* block = new TypeBlock( m_Count, text, record_id );
    this->TypeVariantStruct::Append( *block );
    m_Count += text.size();
}
