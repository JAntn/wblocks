#include "FW/RC/string_record.h"
#include "FW/UI/ui_string_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include <FW/document.h>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#define CLASS_NAME "String"

C_StringRecord::C_StringRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root )
    : C_Record( id, name, value, parent, root )
{
    // void
}

C_StringRecord::C_StringRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root  ):
    C_Record( "", "", "", parent, root )
{
    SetState( state, root );
}

C_StringRecord::~C_StringRecord()
{
    //void
}

QString C_StringRecord::Script()
{
    return "\n" + FullName() + " = \"" + Value().replace( "\n", "\\n" ) + "\""  + ";";
}

QString C_StringRecord::Class() const
{
    return CLASS_NAME;
}

void C_StringRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiStringRecordProperties( *this, document, &document.MainWindow() );
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

void C_StringRecord::SetState( C_StateWriter& state, C_RecordStruct* )
{
    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
}

C_Record* C_StringRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    C_StringRecord* record = new C_StringRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_StringRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    C_StringRecord* record = new C_StringRecord( state, parent, root );
    return record;
}

QString C_StringRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}


