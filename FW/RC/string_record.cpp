#include "FW/RC/string_record.h"
#include "FW/UI/ui_string_editor.h"
#include "FW/UI/ui_main_window.h"
#include <FW/document.h>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#define CLASS_NAME "String"

C_StringRecord::C_StringRecord( QString id, QString name, QString value, C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    // void
}

C_StringRecord::C_StringRecord( C_StateWriter& state, C_Variant* parent )
    : C_Record( "", "", "", parent )
{
    SetState( state );
}

C_StringRecord::~C_StringRecord()
{
    //void
}

QString C_StringRecord::Script() const
{
    return FullName() + " = \"" + Value() + "\""  + ";";
}

C_RecordStruct* C_StringRecord::Struct() const
{
    return 0;
}

QString C_StringRecord::Class() const
{
    return CLASS_NAME;
}

void C_StringRecord::ShowEditor( C_Document& document )
{
    QWidget* dialog = new C_UiStringEditor( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_StringRecord::GetState( C_StateReader& state )
{
    QStringList row;

    row.append( Id() );
    row.append( Name() );
    row.append( Value() );
    row.append( Class() );

    state.Read( row );
}

void C_StringRecord::SetState( C_StateWriter& state )
{
    QStringList row;

    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row.at( 0 );

    m_Name  = row.at( 1 );
    m_Value = row.at( 2 );
}

C_Record* C_StringRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_StringRecord* record = new C_StringRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_StringRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent )
{
    C_StringRecord* record = new C_StringRecord( state, parent );
    return record;
}

QString C_StringRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}


