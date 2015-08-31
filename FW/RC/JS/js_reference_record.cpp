#include "FW/RC/JS/js_reference_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"


TypeJsReferenceRecord::TypeJsReferenceRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeReferenceRecord( id, name, value, parent, root )
{
    m_Class = "JsReference";
}

TypeJsReferenceRecord::TypeJsReferenceRecord( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root ):
    TypeReferenceRecord( state, parent, root )
{
    m_Class = "JsReference";
}

TypeJsReferenceRecord::~TypeJsReferenceRecord()
{
    // void
}

QStringList TypeJsReferenceRecord::Script()
{
    TypeRecord* record = Referencee();

    if( record != 0 )
        return QStringList( "\n" + FullName() + " = " + record->FullName() + ";" );

    qDebug() << "Warning - Bad reference value >" << FullName();
    return QStringList();
}


TypeJsReferenceRecordFactory::TypeJsReferenceRecordFactory()
{
    m_RecordClass = "JsReference";
}

TypeRecord* TypeJsReferenceRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsReferenceRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsReferenceRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsReferenceRecord( state, parent, root );
}
