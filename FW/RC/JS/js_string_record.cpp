#include "FW/BK/html_block_stream.h"
#include "FW/RC/JS/js_string_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsStringRecord::TypeJsStringRecord( QString id, QString name, QString value, TypeVariant* parent , TypeStruct* root ):
    TypeStringRecord( id, name, value, parent, root )
{
    m_Class = "JsString";
}

TypeJsStringRecord::TypeJsStringRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root  ):
    TypeStringRecord( state, parent, root )
{
    m_Class = "JsString";
}

TypeJsStringRecord::~TypeJsStringRecord()
{
    //void
}

void TypeJsStringRecord::Script( TypeHtmlBlockStream& block_stream )
{
    block_stream.Append( "\n" + FullName() + " = \"" + Value().replace( "\n", "\\n" ) + "\""  + ";", Id() );
}

TypeJsStringRecordFactory::TypeJsStringRecordFactory()
{
    m_RecordClass = "JsString";
}

TypeRecord* TypeJsStringRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeStruct* root )
{
    return new TypeJsStringRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsStringRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    return new TypeJsStringRecord( state, parent, root );
}



