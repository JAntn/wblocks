#include "FW/BK/block_stream.h"
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

void TypeHtmlRecord::Html( TypeBlockStream& block_stream )
{
    block_stream.Append( Value(), Id() );
}

TypeHtmlRecordFactory::TypeHtmlRecordFactory()
{
    m_RecordClass = "Html";
}

TypeRecord* TypeHtmlRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeHtmlRecord* record = new TypeHtmlRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

TypeRecord* TypeHtmlRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeHtmlRecord* record = new TypeHtmlRecord( state, parent, root );
    return record;
}


