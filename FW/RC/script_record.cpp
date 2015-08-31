#include "FW/RC/script_record.h"
#include "FW/UI/PR/ui_record_properties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QVBoxLayout>
#include <FW/UI/PR/ui_record_name_property.h>
#include <FW/UI/PR/ui_string_property.h>
#include <FW/UI/ED/ui_text_editor.h>


TypeScriptRecord::TypeScriptRecord( QString id, QString name, QString value, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Script";
}

TypeScriptRecord::TypeScriptRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Script";
    SetState( state, root );
}

TypeScriptRecord::~TypeScriptRecord()
{
    //void
}

QStringList TypeScriptRecord::Script()
{
    return QStringList( Value() );
}

QWidget* TypeScriptRecord::PropertyWidget( TypeController& controller )
{
    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new TypeUiStringProperty( "Script", Value(), [&controller, this]( TypeUiProperty & property_base )
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

TypeUiEditor* TypeScriptRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    text_editor = new TypeUiTextEditor( id, Name(), Name().split( "." ).back(), [&controller, this]( TypeUiEditor & editor_base )
    {
        TypeUiTextEditor& editor = static_cast<TypeUiTextEditor&>( editor_base );
        SetValue( editor.Text() );
        emit controller.RecordsChanged();
    } );

    text_editor->SetText( Value() );

    return text_editor;
}

TypeScriptRecordFactory::TypeScriptRecordFactory()
{
    m_RecordClass = "Script";
}

TypeRecord* TypeScriptRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeScriptRecord* record = new TypeScriptRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

TypeRecord* TypeScriptRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    TypeScriptRecord* record = new TypeScriptRecord( state, parent, root );
    return record;
}



