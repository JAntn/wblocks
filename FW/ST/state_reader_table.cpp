#include "state_reader_table.h"


C_StateReaderTable::C_StateReaderTable( QList<QStringList>& table, long flags, C_Variant* parent )
    : C_StateReader( flags, parent )
{
    m_Table = &table;
}

void C_StateReaderTable::Read(QStringList& data)
{
    if( AtEnd() )
        return;

    m_Table->append(data);
    ++m_Count;
}
