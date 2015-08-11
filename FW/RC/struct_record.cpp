#include "FW/RC/struct_record.h"
#include "FW/document.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_main_window.h"
#include <FW/UI/ui_struct_editor.h>

#define CLASS_NAME "Struct"

C_StructRecord::C_StructRecord( QString id, QString name, QString value, C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    m_Records = new C_RecordStruct( name, this );
}

C_StructRecord::C_StructRecord( C_StateWriter& state, C_Variant* parent )
    : C_Record( "", "", "", parent )
{
    m_Records = new C_RecordStruct( "", this );
    SetState( state );
}

C_StructRecord::~C_StructRecord()
{
    // void
}

QString C_StructRecord::Value() const
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

C_RecordStruct* C_StructRecord::Struct() const
{
    return m_Records;
}

QString C_StructRecord::Script() const
{
    QStringList script;
    script << FullName() << " = {} ;";

    for( C_Variant* node : Records() )
        script << "\n" << static_cast<C_Record*>( node )->Script() ;

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

    for( C_Variant* node : Records() )
    {
        auto record = static_cast<C_Record*>( node );
        record->GetState( state );
    }
}

void C_StructRecord::SetState( C_StateWriter& state )
{
    Records().Clear();

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row.at( 0 );

    m_Name  = row.at( 1 );
    m_Value = row.at( 2 );
    Records().SetName( Name() );
    long size = m_Value.toLong();

    for( long count = 0; count < size; ++count )
        Records().CreateRecord( state );
}

void C_StructRecord::ShowEditor( C_Document& document )
{
    QWidget* dialog = new C_UiStructEditor( *this, document, &document.MainWindow() );
    dialog->show();
}

C_Record* C_StructRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_StructRecord* record = new C_StructRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_StructRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent )
{
    C_StructRecord* record = new C_StructRecord( state, parent );
    return record;
}

QString C_StructRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}
