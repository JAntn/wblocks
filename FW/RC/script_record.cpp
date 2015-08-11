#include "FW/RC/script_record.h"
#include "FW/RC/string_record.h"
#include "FW/RC/record_struct.h"
#include "FW/RC/bool_record.h"
#include "FW/RC/string_record.h"
#include "FW/document.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_script_editor.h"

#define CLASS_NAME "Script"
#include <qDebug>

C_ScriptRecord::C_ScriptRecord( QString id, QString name, QString value,  C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    m_Records = new C_RecordStruct( m_Name, this );
    Records().SetFlags( FLAG_ACTION_EDIT | FLAG_ACTION_ADD_SCENE | FLAG_ACTION_COPY );
    m_IsFromFile = static_cast<C_BoolRecord*>   ( Records().CreateRecord( "IsFromFile", "False", "Bool" ) );
    m_Code       = static_cast<C_StringRecord*> ( Records().CreateRecord( "Code", "//Script: \n", "String" ) );
    m_FileName   = static_cast<C_StringRecord*> ( Records().CreateRecord( "FileName", "", "String" ) );

    m_IsFromFile ->SetFlags( ~FLAG_ACTION_REMOVE );
    m_Code       ->SetFlags( ~FLAG_ACTION_REMOVE );
    m_FileName   ->SetFlags( ~FLAG_ACTION_REMOVE );
}

C_ScriptRecord::C_ScriptRecord( C_StateWriter& state, C_Variant* parent )
    : C_Record( "", "", "", parent )
{
    m_Records = new C_RecordStruct( "", this );
    Records().SetFlags( FLAG_ACTION_EDIT | FLAG_ACTION_ADD_SCENE | FLAG_ACTION_COPY );
    SetState( state );
}

C_ScriptRecord::~C_ScriptRecord()
{
    // void
}

QString C_ScriptRecord::Script() const
{
    return Code().Value();
}

C_RecordStruct* C_ScriptRecord::Struct() const
{
    return m_Records;
}

QString C_ScriptRecord::Value() const
{
    return QString::number( Records().Size() );
}

void C_ScriptRecord::SetValue( QString )
{
    // void
}

QString C_ScriptRecord::Class() const
{
    return CLASS_NAME;
}


void C_ScriptRecord::GetState( C_StateReader& state )
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

void C_ScriptRecord::SetState( C_StateWriter& state )
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
    int size = m_Value.toInt();

    for( int count = 0; count < size; ++count )
        Records().CreateRecord( state );

    m_IsFromFile = static_cast<C_BoolRecord*>( Records().FromName( "IsFromFile" ) );
    m_FileName   = static_cast<C_StringRecord*>( Records().FromName( "FileName" ) );
    m_Code       = static_cast<C_StringRecord*>( Records().FromName( "Code" ) );

    m_IsFromFile ->SetFlags( ~FLAG_ACTION_REMOVE );
    m_Code       ->SetFlags( ~FLAG_ACTION_REMOVE );
    m_FileName   ->SetFlags( ~FLAG_ACTION_REMOVE );

    if( IsFromFile().Value() == "True" )
        Code().SetValue( C_Document::LoadTextFile( FileName().Value() ) );
}

void C_ScriptRecord::ShowEditor( C_Document& document )
{
    QWidget* dialog = new C_UiScriptEditor( *this, document, &document.MainWindow() );
    dialog->show();
}

C_Record* C_ScriptRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_ScriptRecord* record = new C_ScriptRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_ScriptRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent )
{
    C_ScriptRecord* record = new C_ScriptRecord( state, parent );
    return record;
}

QString C_ScriptRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

