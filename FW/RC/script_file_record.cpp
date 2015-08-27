#include "FW/RC/script_file_record.h"
#include "FW/RC/record_struct.h"
#include "FW/document.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/PR/ui_script_file_record_properties.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/RC/file_record.h"
#include "FW/UI/ui_file_text_editor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QFileInfo>
#include <QCoreApplication>


C_ScriptFileRecord::C_ScriptFileRecord( QString id, QString name, QString value,  C_Variant* parent, C_RecordStruct* root ):
    C_FileRecord( id, name, value, parent, root )
{
    m_Class = "ScriptFile";
}

C_ScriptFileRecord::C_ScriptFileRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_FileRecord( state, parent, root )
{
    m_Class = "ScriptFile";
}

C_ScriptFileRecord::~C_ScriptFileRecord()
{
    // void
}

QStringList C_ScriptFileRecord::Script()
{
    return QStringList( C_Document::LoadTextFile( FileFullName() ) );
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

    QString editor_id = "FILE:TEXT:" + FileFullName();
    QString file_name = FileFullName();

    if( main_window.TextEditorContainer().HasId( editor_id ) )
    {
        if( C_Document::AcceptMessage(
                    QCoreApplication::translate( "C_ScriptFileRecord", "File already opened.\n\nLoad again?" ) ) )
        {
            main_window.TextEditorContainer().Close( editor_id );
            main_window.TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
            emit document.Events().TextEditorContainerChanged();
            main_window.SetCurrentTab( MAINWINDOW_TAB_EDITOR );
        }

        emit document.Events().RecordsChanged();
        return;
    }

    if( !QFileInfo( file_name ).exists() )
    {
        if( C_Document::AcceptMessage(
                    QCoreApplication::translate( "C_ScriptFileRecord", "File doesn't exists.\nCreate a new file?" ) ) )
            C_Document::SaveTextFile( file_name, "" );
    }

    main_window.TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
    emit document.Events().TextEditorContainerChanged();
    main_window.SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

C_ScriptFileRecordFactory::C_ScriptFileRecordFactory()
{
    m_RecordClass = "ScriptFile";
}

C_Record* C_ScriptFileRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_ScriptFileRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_ScriptFileRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_ScriptFileRecord( state, parent, root );
}



