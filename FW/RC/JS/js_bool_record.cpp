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

QStringList TypeJsBoolRecord::Script()
{
    return QStringList( "\n" + FullName() + " = " + Value() + ";" );
}

TypeJsBoolRecordFactory::TypeJsBoolRecordFactory()
{
    m_RecordClass = "JsBool";
}

TypeRecord* TypeJsBoolRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsBoolRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsBoolRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsBoolRecord( state, parent, root );
}




