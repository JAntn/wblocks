#include "FW/RC/file_record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"
#include <QFileDialog>
#include <QMainWindow>

#define CLASS_NAME "File"

C_FileRecord::C_FileRecord( QString id, QString name, QString value, C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    if( m_Value.isEmpty() )
        m_Value = "unnamed";
}

C_FileRecord::C_FileRecord( C_StateWriter& state, C_Variant* parent )
    : C_Record( "", "", "", parent )
{
    SetState( state );
}

C_FileRecord::~C_FileRecord()
{
    //void
}

QString C_FileRecord::Script() const
{
    return FullName() + " = \"" + Value() + "\""  + ";";
}

C_RecordStruct* C_FileRecord::Struct() const
{
    return 0;
}

QString C_FileRecord::Class() const
{
    return CLASS_NAME;
}

void C_FileRecord::ShowEditor( C_Document& document )
{
    QString file_name = QFileDialog::getOpenFileName(
                            &document.MainWindow(),
                            QFileDialog::tr("Select file"),
                            Value(),
                            "*.*"  );

    if( file_name.isEmpty() )
        file_name = "unnamed";

    m_Value = file_name;
    emit document.Events().RecordsChanged();
}

QString C_FileRecord::FileDir()
{
    QStringList string_list = Value().split("/");
    string_list.pop_back();
    return string_list.join("/");
}

QString C_FileRecord::FileName()
{
    return Value().split("/").back();
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

void C_FileRecord::SetState( C_StateWriter& state )
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

C_Record* C_FileRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_FileRecord* record = new C_FileRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_FileRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent )
{
    C_FileRecord* record = new C_FileRecord( state, parent );
    return record;
}

QString C_FileRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}


