#include "FW/RC/JS/js_reference_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


C_JsReferenceRecord::C_JsReferenceRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_ReferenceRecord( id, name, value, parent, root )
{
    m_Class = "JsReference";
}

C_JsReferenceRecord::C_JsReferenceRecord( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root ):
    C_ReferenceRecord( state, parent, root )
{
    m_Class = "JsReference";
}

C_JsReferenceRecord::~C_JsReferenceRecord()
{
    // void
}

QStringList C_JsReferenceRecord::Script()
{
    C_Record* record = Referencee();

    if( record != 0 )
        return QStringList( "\n" + FullName() + " = " + record->FullName() + ";" );

    qDebug() << "Warning - Bad reference value >" << FullName();
    return QStringList();
}


C_JsReferenceRecordFactory::C_JsReferenceRecordFactory()
{
    m_RecordClass = "JsReference";
}

C_Record* C_JsReferenceRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_JsReferenceRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_JsReferenceRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_JsReferenceRecord( state, parent, root );
}
