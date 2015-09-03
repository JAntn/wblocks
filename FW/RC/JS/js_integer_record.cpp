#include "FW/BK/block_stream.h"
#include "FW/RC/JS/js_integer_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsIntegerRecord::TypeJsIntegerRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeIntegerRecord( id, name, value, parent, root )
{
    m_Class = "JsInteger";
}

TypeJsIntegerRecord::TypeJsIntegerRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeIntegerRecord( state, parent, root )
{
    m_Class = "JsInteger";
}

TypeJsIntegerRecord::~TypeJsIntegerRecord()
{
    //void
}

void TypeJsIntegerRecord::Script( TypeBlockStream& block_stream )
{
    block_stream.Append( "\n" + FullName() + " = " + Value() + ";" , Id() );
}

TypeJsIntegerRecordFactory::TypeJsIntegerRecordFactory()
{
    m_RecordClass = "JsInteger";
}

TypeRecord* TypeJsIntegerRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsIntegerRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsIntegerRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsIntegerRecord( state, parent, root );
}





