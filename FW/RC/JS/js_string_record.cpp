#include "FW/RC/JS/js_string_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


C_JsStringRecord::C_JsStringRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_StringRecord( id, name, value, parent, root )
{
    m_Class = "JsString";
}

C_JsStringRecord::C_JsStringRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root  ):
    C_StringRecord( state, parent, root )
{
    m_Class = "JsString";
}

C_JsStringRecord::~C_JsStringRecord()
{
    //void
}

QStringList C_JsStringRecord::Script()
{
    return QStringList( "\n" + FullName() + " = \"" + Value().replace( "\n", "\\n" ) + "\""  + ";" );
}

C_JsStringRecordFactory::C_JsStringRecordFactory()
{
    m_RecordClass = "JsString";
}

C_Record* C_JsStringRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_JsStringRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_JsStringRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_JsStringRecord( state, parent, root );
}



