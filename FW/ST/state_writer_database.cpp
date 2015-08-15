#include "FW/ST/state_writer_database.h"

C_StateWriterDatabase::C_StateWriterDatabase( C_Database& database,
        QString table_name, QString field_name, long size, long flags, C_Variant* parent ):
    C_StateWriter( flags, parent )
{
    m_Database = &database;
    m_TableName = table_name;
    m_FieldName = field_name;
    m_Size = size;

    if( m_Size < 1 )
    {
        Stop();
        return;
    }

    QStringList tmp = m_Database->GetRecord(
                          TableName(), FieldName(), QString::number( Count() ) );
    tmp.pop_front();
    m_Data = tmp;
}

void C_StateWriterDatabase::Next()
{
    if( AtEnd() )
        return;

    ++m_Count;

    if( m_Size <= m_Count )
    {
        Stop();
        return;
    }

    QStringList tmp = m_Database->GetRecord(
                          TableName(), FieldName(), QString::number( Count() ) );
    tmp.pop_front();
    m_Data = tmp;
}
