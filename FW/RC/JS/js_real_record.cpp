
#include "FW/RC/JS/js_real_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


C_JsRealRecord::C_JsRealRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_RealRecord( id, name, value, parent, root )
{
    m_Class = "JsReal" ;
}

C_JsRealRecord::C_JsRealRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_RealRecord( state, parent, root )
{
    m_Class = "JsReal" ;
}

C_JsRealRecord::~C_JsRealRecord()
{
    //void
}

QStringList C_JsRealRecord::Script()
{
    return  QStringList( "\n" + FullName() + " = " + Value() + ";" );
}

C_JsRealRecordFactory::C_JsRealRecordFactory()
{
    m_RecordClass = "JsReal";
}

C_Record* C_JsRealRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_JsRealRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_JsRealRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_JsRealRecord( state, parent, root );
}




