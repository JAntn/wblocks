#include "FW/RC/script_file_record.h"
#include "FW/RC/record_struct.h"
#include "FW/document.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_script_file_record_properties.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/RC/file_record.h"
#include "FW/UI/ui_file_text_editor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QFileInfo>

#define CLASS_NAME "ScriptFile"

C_ScriptFileRecord::C_ScriptFileRecord( QString id, QString name, QString value,  C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Records = new C_RecordStruct( m_Name, this );
    Records().SetFlags( FLAG_ACTION_ALL );

    m_File = static_cast<C_FileRecord*> ( Records().CreateRecord( "File", "", "File" ) );
    m_File ->SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_Code = "";
}

C_ScriptFileRecord::C_ScriptFileRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Records = new C_RecordStruct( "", this );
    Records().SetFlags( FLAG_ACTION_ALL );
    SetState( state, root );
}

C_ScriptFileRecord::~C_ScriptFileRecord()
{
    // void
}

QString C_ScriptFileRecord::Script()
{
    m_Code = C_Document::LoadTextFile( File().FileFullName() );
    return "\n" + m_Code;
}

C_RecordStruct* C_ScriptFileRecord::Struct()
{
    return m_Records;
}

QString C_ScriptFileRecord::Value()
{
    return QString::number( Records().Size() );
}

void C_ScriptFileRecord::SetValue( QString )
{
    // void
}

QString C_ScriptFileRecord::Class() const
{
    return CLASS_NAME;
}


void C_ScriptFileRecord::GetState( C_StateReader& state )
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

void C_ScriptFileRecord::SetState(C_StateWriter& state , C_RecordStruct* root)
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
    int size = m_Value.toInt();

    for( int count = 0; count < size; ++count )
        Records().CreateRecord( state, -1, root );

    m_File = static_cast<C_FileRecord*>( Records().FromName( "File" ) );
    File().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_Code = "";
}

void C_ScriptFileRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiScriptFileRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_ScriptFileRecord::OpenInEditor( C_Document& document )
{

    // OPEN THE FILE OR CREATE AN EMPTY ONE

    auto& main_window = document.MainWindow();

    QString editor_id = "FILE:TEXT:" + File().FileFullName();
    QString file_name = File().FileFullName();

    if( main_window.TextEditorContainer().HasId( editor_id ) )
    {
        if( C_Document::AcceptMessage( "File already opened.\n\nLoad again?" ) )
        {
            main_window.TextEditorContainer().Close( editor_id );
            main_window.TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
            emit document.Events().TextEditorContainerChanged();
            main_window.SetCurrentTab( MAINWINDOW_TAB_EDITOR );
        }

        emit document.Events().RecordsChanged();
        return;
    }

    if( !QFileInfo( File().FileFullName() ).exists() )
        C_Document::SaveTextFile( File().FileFullName(), "" );

    main_window.TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
    emit document.Events().TextEditorContainerChanged();
    main_window.SetCurrentTab( MAINWINDOW_TAB_EDITOR );

}

C_Record* C_ScriptFileRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_ScriptFileRecord* record = new C_ScriptFileRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_ScriptFileRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_ScriptFileRecord* record = new C_ScriptFileRecord( state, parent, root );
    return record;
}

QString C_ScriptFileRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

