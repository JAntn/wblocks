#include "FW/RC/file_record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/UI/ui_file_record_properties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#define CLASS_NAME "File"

C_FileRecord::C_FileRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    if( m_Value.isEmpty() )
        m_Value = "untitled";
}

C_FileRecord::C_FileRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    SetState( state, root );
}

C_FileRecord::~C_FileRecord()
{
    //void
}

QString C_FileRecord::Script()
{
    return "\n" + FullName() + " = \"" + Value() + "\""  + ";";
}

QString C_FileRecord::Class() const
{
    return CLASS_NAME;
}

void C_FileRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiFileRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

QString C_FileRecord::FilePath()
{
    QStringList string_list = Value().split( "/" );
    string_list.pop_back();
    return string_list.join( "/" );
}

QString C_FileRecord::FileName()
{
    return Value().split( "/" ).back();
}

QString C_FileRecord::FileFullName()
{
    return Value();
}

void C_FileRecord::GetState( C_StateReader& state )
{
    QStringList row;

    row.append( Id() );
    row.append( Name() );
    row.append( Value() );
    row.append( Class() );

    state.Read( row );
}

void C_FileRecord::SetState( C_StateWriter& sate, C_RecordStruct* )
{
    QStringList row;

    sate.Write( row );

    if( sate.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
}

C_Record* C_FileRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_FileRecord* record = new C_FileRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_FileRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_FileRecord* record = new C_FileRecord( state, parent, root );
    return record;
}

QString C_FileRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}


