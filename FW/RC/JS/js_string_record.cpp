#include "FW/RC/JS/js_string_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsStringRecord::TypeJsStringRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeStringRecord( id, name, value, parent, root )
{
    m_Class = "JsString";
}

TypeJsStringRecord::TypeJsStringRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root  ):
    TypeStringRecord( state, parent, root )
{
    m_Class = "JsString";
}

TypeJsStringRecord::~TypeJsStringRecord()
{
    //void
}

QStringList TypeJsStringRecord::Script()
{
    return QStringList( "\n" + FullName() + " = \"" + Value().replace( "\n", "\\n" ) + "\""  + ";" );
}

TypeJsStringRecordFactory::TypeJsStringRecordFactory()
{
    m_RecordClass = "JsString";
}

TypeRecord* TypeJsStringRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsStringRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsStringRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeJsStringRecord( state, parent, root );
}



