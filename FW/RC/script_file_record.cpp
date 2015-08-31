#include "FW/RC/script_file_record.h"
#include "FW/RC/record_struct.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/RC/file_record.h"
#include <QFileInfo>
#include <QCoreApplication>
#include "FW/UI/ED/ui_text_editor.h"

#include "FW/document.h"
#include "FW/UI/ui_main_window.h"

#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"



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
    return QStringList( C_Controller::LoadTextFile( FileFullName() ) );
}

C_UiEditor* C_ScriptFileRecord::EditorWidget( QString id, C_Controller& controller )
{
    C_UiTextEditor* text_editor;

    text_editor = new C_UiTextEditor( id, FileName(), FileName().split( "/" ).back(), [&controller, this]( C_UiEditor & editor_base )
    {
        C_UiTextEditor& editor = static_cast<C_UiTextEditor&>( editor_base );
        C_Controller::SaveTextFile( FileFullName(), editor.Text() );
        emit controller.RecordsChanged();
    } );

    text_editor->SetText( C_Controller::LoadTextFile( FileFullName() ) );

    return text_editor;
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



