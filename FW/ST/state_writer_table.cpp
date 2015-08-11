#include "FW/ST/state_writer_table.h"


C_StateWriterTable::C_StateWriterTable( list<QStringList>& table, long flags, C_Variant* parent )
    : C_StateWriter( flags, parent )
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

void C_StateWriterTable::Next()
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
