#include "FW/RC/JS/js_bool_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

C_JsBoolRecord::C_JsBoolRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_BoolRecord( id, name, value, parent, root )
{
    m_Class = "JsBool" ;
}

C_JsBoolRecord::C_JsBoolRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_BoolRecord( state, parent, root )
{
    m_Class = "JsBool" ;
}

C_JsBoolRecord::~C_JsBoolRecord()
{
    //void
}

QStringList C_JsBoolRecord::Script()
{
    return QStringList( "\n" + FullName() + " = " + Value() + ";" );
}

C_JsBoolRecordFactory::C_JsBoolRecordFactory()
{
    m_RecordClass = "JsBool";
}

C_Record* C_JsBoolRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_JsBoolRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_JsBoolRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_JsBoolRecord( state, parent, root );
}




