#include "FW/tools.h"
#include "FW/RC/PHP/php_file_record.h"
#include "FW/RC/record_struct.h"
#include "FW/RC/file_record.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/BK/block_stream.h"
#include "FW/UI/SH/ui_syntax_highlighter_factory.h"

TypePhpFileRecord::TypePhpFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeRecordStruct* root ):
    TypeFileRecord( id, name, value, parent, root )
{
    m_Class = "PhpFile";
}

TypePhpFileRecord::TypePhpFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeFileRecord( state, parent, root )
{
    m_Class = "PhpFile";
}

TypePhpFileRecord::~TypePhpFileRecord()
{
    // void
}

TypeUiEditor* TypePhpFileRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    TypeUiSyntaxHighlighter* syntax_highlighter = controller.SyntaxHighlighterFactory().NewInstance( "PHP" );

    text_editor = new TypeUiTextEditor(
        id, FileName(), FileName().split( "/" ).back(), 0/*parent widget*/,
        [&controller, this]( TypeUiEditor & editor_base )/*save callback*/
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        TypeController::SaveTextFile( FileFullName(), editor->Text() );
        emit controller.RecordsChanged();
    },
    syntax_highlighter );

    text_editor->SetText( TypeController::LoadTextFile( FileFullName() ) );

    return text_editor;
}

TypePhpFileRecordFactory::TypePhpFileRecordFactory()
{
    m_RecordClass = "PhpFile";
}

TypeRecord* TypePhpFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypePhpFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypePhpFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypePhpFileRecord( state, parent, root );
}



