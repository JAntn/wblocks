
#include "FW/RC/JS/js_real_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsRealRecord::TypeJsRealRecord( QString id, QString name, QString value, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRealRecord( id, name, value, parent, root )
{
    m_Class = "JsReal" ;
}

TypeJsRealRecord::TypeJsRealRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRealRecord( state, parent, root )
{
    m_Class = "JsReal" ;
}

TypeJsRealRecord::~TypeJsRealRecord()
{
    //void
}

QStringList TypeJsRealRecord::Script()
{
    return  QStringList( "\n" + FullName() + " = " + Value() + ";" );
}

TypeJsRealRecordFactory::TypeJsRealRecordFactory()
{
    m_RecordClass = "JsReal";
}

TypeRecord* TypeJsRealRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsRealRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsRealRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsRealRecord( state, parent, root );
}




