#include "FW/ST/state_writer_database.h"

TypeStateWriterDatabase::TypeStateWriterDatabase( TypeDatabase& database,
        QString table_name, QString field_name, long size, long flags, TypeVariant* parent ):
    TypeStateWriter( flags, parent )
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

void TypeStateWriterDatabase::Next()
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
