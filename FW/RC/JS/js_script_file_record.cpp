#include "FW/tools.h"
#include "FW/RC/JS/js_script_file_record.h"
#include "FW/RC/struct.h"
#include "FW/RC/file_record.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/BK/html_block_stream.h"
#include "FW/UI/SH/ui_syntax_highlighter_factory.h"

TypeJsScriptFileRecord::TypeJsScriptFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeStruct* root ):
    TypeFileRecord( id, name, value, parent, root )
{
    m_Class = "JsScriptFile";
}

TypeJsScriptFileRecord::TypeJsScriptFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeFileRecord( state, parent, root )
{
    m_Class = "JsScriptFile";
}

TypeJsScriptFileRecord::~TypeJsScriptFileRecord()
{
    // void
}

void TypeJsScriptFileRecord::Html( TypeHtmlBlockStream& block_stream )
{
    QStringList html;
    html << "\n<script type=\"text\\javascript\" src=\"" << FileName() <<"\"></script>";
    block_stream.Append( html.join(""), Id() );
}

TypeUiEditor* TypeJsScriptFileRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    TypeUiSyntaxHighlighter* syntax_highlighter = controller.SyntaxHighlighterFactory().NewInstance("JS");

    text_editor = new TypeUiTextEditor(
                id, FileName(), FileName().split( "/" ).back(), 0/*parent widget*/,
                [&controller, this]( TypeUiEditor & editor_base )/*save callback*/
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        TypeController::SaveTextFile( FileFullName(), editor->Text() );
        emit controller.RecordsChanged();
        return true;
    },
    syntax_highlighter);

    text_editor->SetText( TypeController::LoadTextFile( FileFullName() ) );
    text_editor->SetHasChanged(false);

    return text_editor;
}

TypeJsScriptFileRecordFactory::TypeJsScriptFileRecordFactory()
{
    m_RecordClass = "JsScriptFile";
}

TypeRecord* TypeJsScriptFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeJsScriptFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsScriptFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeJsScriptFileRecord( state, parent, root );
}



