#include "FW/tools.h"
#include "FW/BK/block_stream.h"
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

void TypeJsReferenceRecord::Script( TypeBlockStream& block_stream )
{
    TypeRecord* record = Referencee();

    if( record != 0 ){
        block_stream.Append( "\n" + FullName() + " = " + record->FullName() + ";", Id() );
        return;
    }

    qDebug() << "Warning - Bad reference value >" << FullName();
}


TypeJsReferenceRecordFactory::TypeJsReferenceRecordFactory()
{
    m_RecordClass = "JsReference";
}

TypeRecord* TypeJsReferenceRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsReferenceRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsReferenceRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeJsReferenceRecord( state, parent, root );
}
