#include "state_reader_database.h"

C_StateReaderDatabase::C_StateReaderDatabase(C_Database& database,
        QString table_name, QString field_name, long flags, C_Variant* parent )
    : C_StateReader( flags, parent )
{
    m_Database = &database;
    m_TableName = table_name;
    m_FieldName = field_name;
}

void C_StateReaderDatabase::Read(QStringList &data)
{
    if( AtEnd() )
        return;

    QStringList tmp = data;
    tmp.push_front( QString::number( m_Count ) );
    m_Database->AppendRecord( m_TableName, tmp );
    ++m_Count;
}
