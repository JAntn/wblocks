#include "FW/RC/HTML/html_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

TypeHtmlRecord::TypeHtmlRecord( QString id, QString name, QString value, TypeVariant* parent, TypeRecordStruct* root ):
    TypeStringRecord( id, name, value, parent, root )
{
    m_Class = "Html";
}

TypeHtmlRecord::TypeHtmlRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeStringRecord( "", "", "", parent, root )
{
    m_Class = "Html";
    SetState( state, root );
}

TypeHtmlRecord::~TypeHtmlRecord()
{
    //void
}

QStringList TypeHtmlRecord::Html()
{
    return QStringList( Value() );
}

TypeHtmlRecordFactory::TypeHtmlRecordFactory()
{
    m_RecordClass = "Html";
}

TypeRecord* TypeHtmlRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeHtmlRecord* record = new TypeHtmlRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

TypeRecord* TypeHtmlRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeHtmlRecord* record = new TypeHtmlRecord( state, parent, root );
    return record;
}


