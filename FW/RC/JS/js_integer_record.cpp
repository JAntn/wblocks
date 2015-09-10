#include "FW/BK/html_block_stream.h"
#include "FW/RC/JS/js_integer_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsIntegerRecord::TypeJsIntegerRecord( QString id, QString name, QString value, TypeVariant* parent , TypeStruct* root ):
    TypeIntegerRecord( id, name, value, parent, root )
{
    m_Class = "JsInteger";
}

TypeJsIntegerRecord::TypeJsIntegerRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeIntegerRecord( state, parent, root )
{
    m_Class = "JsInteger";
}

TypeJsIntegerRecord::~TypeJsIntegerRecord()
{
    //void
}

void TypeJsIntegerRecord::Script( TypeHtmlBlockStream& block_stream )
{
    block_stream.Append( "\n" + FullName() + " = " + Value() + ";" , Id() );
}

TypeJsIntegerRecordFactory::TypeJsIntegerRecordFactory()
{
    m_RecordClass = "JsInteger";
}

TypeRecord* TypeJsIntegerRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeStruct* root )
{
    return new TypeJsIntegerRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsIntegerRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    return new TypeJsIntegerRecord( state, parent, root );
}





