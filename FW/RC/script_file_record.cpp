#include "FW/RC/script_file_record.h"
#include "FW/RC/record_struct.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/RC/file_record.h"
#include <QFileInfo>
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"



TypeScriptFileRecord::TypeScriptFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeRecordStruct* root ):
    TypeFileRecord( id, name, value, parent, root )
{
    m_Class = "ScriptFile";
}

TypeScriptFileRecord::TypeScriptFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeFileRecord( state, parent, root )
{
    m_Class = "ScriptFile";
}

TypeScriptFileRecord::~TypeScriptFileRecord()
{
    // void
}

QStringList TypeScriptFileRecord::Script()
{
    return QStringList( TypeController::LoadTextFile( FileFullName() ) );
}

TypeUiEditor* TypeScriptFileRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    text_editor = new TypeUiTextEditor( id, FileName(), FileName().split( "/" ).back(), [&controller, this]( TypeUiEditor & editor_base )
    {
        TypeUiTextEditor& editor = static_cast<TypeUiTextEditor&>( editor_base );
        TypeController::SaveTextFile( FileFullName(), editor.Text() );
        emit controller.RecordsChanged();
    } );

    text_editor->SetText( TypeController::LoadTextFile( FileFullName() ) );

    return text_editor;
}

TypeScriptFileRecordFactory::TypeScriptFileRecordFactory()
{
    m_RecordClass = "ScriptFile";
}

TypeRecord* TypeScriptFileRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeScriptFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeScriptFileRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeScriptFileRecord( state, parent, root );
}



