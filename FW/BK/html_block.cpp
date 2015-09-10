#include "FW/BK/html_block.h"

TypeHtmlBlock::TypeHtmlBlock( int position, QString text, QString record_id, TypeVariant* parent ):
    TypeVariant( parent ), m_Position( position ), m_Text( text ), m_RecordId( record_id ), m_Selected( false )
{
    // void
}
