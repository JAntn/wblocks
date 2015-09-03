#include "FW/BK/block_stream.h"
#include "FW/RC/JS/js_bool_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

TypeJsBoolRecord::TypeJsBoolRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeBoolRecord( id, name, value, parent, root )
{
    m_Class = "JsBool" ;
}

TypeJsBoolRecord::TypeJsBoolRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeBoolRecord( state, parent, root )
{
    m_Class = "JsBool" ;
}

TypeJsBoolRecord::~TypeJsBoolRecord()
{
    //void
}

void TypeJsBoolRecord::Script( TypeBlockStream& block_stream )
{
    block_stream.Append( "\n" + FullName() + " = " + Value() + ";" , Id() );
}

TypeJsBoolRecordFactory::TypeJsBoolRecordFactory()
{
    m_RecordClass = "JsBool";
}

TypeRecord* TypeJsBoolRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsBoolRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsBoolRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsBoolRecord( state, parent, root );
}




