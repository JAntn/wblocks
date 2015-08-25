#include "FW/document.h"
#include "FW/RC/struct_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_struct_record_properties.h"

#define CLASS_NAME "Struct"

C_StructRecord::C_StructRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Records = new C_RecordStruct( name, this );
}

C_StructRecord::C_StructRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Records = new C_RecordStruct( "", this );
    SetState( state, root );
}

C_StructRecord::~C_StructRecord()
{
    // void
}

QString C_StructRecord::Value()
{
    return QString::number( Records().Size() );
}

void C_StructRecord::SetValue( QString )
{
    // void
}

QString C_StructRecord::Class() const
{
    return CLASS_NAME;
}

C_RecordStruct* C_StructRecord::Struct()
{
    return m_Records;
}

QString C_StructRecord::Script()
{
    QStringList script;
    script << ( "\n" + FullName() + " = {} ;" );

    for( C_Variant* variant : Records() )
        script << static_cast<C_Record*>( variant )->Script() ;

    return script.join( "" );
}

void C_StructRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( Id() );
    row.append( Name() );
    row.append( Value() );
    row.append( Class() );
    state.Read( row );

    for( C_Variant* variant : Records() )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        record->GetState( state );
    }
}

void C_StructRecord::SetState( C_StateWriter& state, C_RecordStruct* root )
{
    Records().Clear();

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
    Records().SetName( Name() );
    long size = m_Value.toLong();

    for( long count = 0; count < size; ++count )
        Records().CreateRecord( state, -1, root );
}

void C_StructRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiStructRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

C_Record* C_StructRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root  )
{
    C_StructRecord* record = new C_StructRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_StructRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    C_StructRecord* record = new C_StructRecord( state, parent, root );
    return record;
}

QString C_StructRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}
