#include "FW/ST/state_reader_table.h"


TypeStateReaderTable::TypeStateReaderTable( QList<QStringList>& table, long flags, TypeVariant* parent ):
    TypeStateReader( flags, parent )
{
    m_Table = &table;
}

void TypeStateReaderTable::Read( QStringList& data )
{
    if( AtEnd() )
        return;

    m_Table->append( data );
    ++m_Count;
}
