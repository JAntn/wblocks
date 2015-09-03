#include "FW/tools.h"
#include "FW/RC/JS/js_script_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/UI/PR/ui_string_property.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/BK/block_stream.h"
#include "FW/UI/SH/ui_syntax_highlighter_factory.h"
#include <QVBoxLayout>


TypeJsScriptRecord::TypeJsScriptRecord( QString id, QString name, QString value, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "JsScript";
}

TypeJsScriptRecord::TypeJsScriptRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "JsScript";
    SetState( state, root );
}

TypeJsScriptRecord::~TypeJsScriptRecord()
{
    //void
}

void TypeJsScriptRecord::Script( TypeBlockStream& block_stream )
{
    block_stream.Append( Value(), Id() );
}

QWidget* TypeJsScriptRecord::PropertyWidget( TypeController& controller )
{
    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        SetName( TypeVariantPtr<TypeUiRecordNameProperty>( &property_base )->Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new TypeUiStringProperty( "JsScript", Value(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiStringProperty&>( property_base );
        SetValue( property.Value() );
        emit controller.RecordsChanged();
    } );


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( name_widget );
    layout->addWidget( value_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

TypeUiEditor* TypeJsScriptRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    TypeUiSyntaxHighlighter* syntax_higlighter = controller.SyntaxHighlighterFactory().NewInstance( "JS" );

    text_editor = new TypeUiTextEditor(
        id, Name(), Name().split( "." ).back(),  0/*parent widget*/,
        [&controller, this]( TypeUiEditor & editor_base )/*save callback*/
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        SetValue( editor->Text() );
        emit controller.RecordsChanged();
    }, syntax_higlighter );

    text_editor->SetText( Value() );

    return text_editor;
}

TypeJsScriptRecordFactory::TypeJsScriptRecordFactory()
{
    m_RecordClass = "JsScript";
}

TypeRecord* TypeJsScriptRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeJsScriptRecord* record = new TypeJsScriptRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

TypeRecord* TypeJsScriptRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeJsScriptRecord* record = new TypeJsScriptRecord( state, parent, root );
    return record;
}



