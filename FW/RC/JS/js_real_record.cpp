#include "FW/BK/html_block_stream.h"
#include "FW/RC/JS/js_real_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsRealRecord::TypeJsRealRecord( QString id, QString name, QString value, TypeVariant* parent, TypeStruct* root ):
    TypeRealRecord( id, name, value, parent, root )
{
    m_Class = "JsReal" ;
}

TypeJsRealRecord::TypeJsRealRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeRealRecord( state, parent, root )
{
    m_Class = "JsReal" ;
}

TypeJsRealRecord::~TypeJsRealRecord()
{
    //void
}

void TypeJsRealRecord::Script( TypeHtmlBlockStream& block_stream )
{
    block_stream.Append( "\n" + FullName() + " = " + Value() + ";", Id() );
}

TypeJsRealRecordFactory::TypeJsRealRecordFactory()
{
    m_RecordClass = "JsReal";
}

TypeRecord* TypeJsRealRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeStruct* root )
{
    return new TypeJsRealRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsRealRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    return new TypeJsRealRecord( state, parent, root );
}




