#include "FW/RC/JS/js_integer_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


C_JsIntegerRecord::C_JsIntegerRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_IntegerRecord( id, name, value, parent, root )
{
    m_Class = "JsInteger";
}

C_JsIntegerRecord::C_JsIntegerRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_IntegerRecord( state, parent, root )
{
    m_Class = "JsInteger";
}

C_JsIntegerRecord::~C_JsIntegerRecord()
{
    //void
}

QStringList C_JsIntegerRecord::Script()
{
    return QStringList( "\n" + FullName() + " = " + Value() + ";" );
}

C_JsIntegerRecordFactory::C_JsIntegerRecordFactory()
{
    m_RecordClass = "JsInteger";
}

C_Record* C_JsIntegerRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_JsIntegerRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_JsIntegerRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_JsIntegerRecord( state, parent, root );
}





