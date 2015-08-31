#include "FW/ST/state_reader_database.h"

TypeStateReaderDatabase::TypeStateReaderDatabase(
    TypeDatabase& database,
    QString table_name,
    QString field_name,
    long flags,
    TypeVariant* parent ):
    TypeStateReader( flags, parent )
{
    m_Database = &database;
    m_TableName = table_name;
    m_FieldName = field_name;
}

void TypeStateReaderDatabase::Read( QStringList& data )
{
    if( AtEnd() )
        return;

    QStringList tmp = data;
    tmp.push_front( QString::number( m_Count ) );
    m_Database->AppendRecord( m_TableName, tmp );
    ++m_Count;
}
