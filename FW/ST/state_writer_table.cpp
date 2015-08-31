#include "FW/ST/state_writer_table.h"

TypeStateWriterTable::TypeStateWriterTable( QList<QStringList>& table, long flags, TypeVariant* parent )
    : TypeStateWriter( flags, parent )
{
    m_Table = &table;
    m_Iter = table.begin();

    if( Iter() == Table().end() )
    {
        Stop();
        return;
    }

    m_Data = *m_Iter;
}

void TypeStateWriterTable::Next()
{
    if( AtEnd() )
        return;

    ++m_Iter;
    ++m_Count;

    if( Iter() == Table().end() )
    {
        Stop();
        return;
    }

    m_Data = *m_Iter;
}
