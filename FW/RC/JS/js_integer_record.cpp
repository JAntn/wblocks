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

QStringList TypeJsIntegerRecord::Script()
{
    return QStringList( "\n" + FullName() + " = " + Value() + ";" );
}

TypeJsIntegerRecordFactory::TypeJsIntegerRecordFactory()
{
    m_RecordClass = "JsInteger";
}

TypeRecord* TypeJsIntegerRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsIntegerRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsIntegerRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsIntegerRecord( state, parent, root );
}





