#include "FW/BK/block.h"

TypeBlock::TypeBlock( int position, QString text, QString record_id, TypeVariant* parent ):
    TypeVariant( parent ), m_Position( position ), m_Text( text ), m_RecordId( record_id )
{
    // void
}
