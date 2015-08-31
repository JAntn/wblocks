#include "FW/RC/script_record.h"
#include "FW/UI/PR/ui_record_properties.h"

#include "FW/UI/ui_editor_container.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QCoreApplication>
#include <QVBoxLayout>
#include <FW/UI/PR/ui_record_name_property.h>
#include <FW/UI/PR/ui_string_property.h>
#include <FW/UI/ED/ui_text_editor.h>

#include "FW/UI/ui_main_window.h"
#include "FW/document.h"

C_ScriptRecord::C_ScriptRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Script";
}

C_ScriptRecord::C_ScriptRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Script";
    SetState( state, root );
}

C_ScriptRecord::~C_ScriptRecord()
{
    //void
}

QStringList C_ScriptRecord::Script()
{
    return QStringList( Value() );
}

QWidget* C_ScriptRecord::PropertyWidget( C_Controller& controller )
{
    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new C_UiStringProperty( "Script", Value(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiStringProperty&>( property_base );
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

C_UiEditor* C_ScriptRecord::EditorWidget( QString id, C_Controller& controller )
{
    C_UiTextEditor* text_editor;

    text_editor = new C_UiTextEditor( id, Name(), Name().split( "." ).back(), [&controller, this]( C_UiEditor & editor_base )
    {
        C_UiTextEditor& editor = static_cast<C_UiTextEditor&>( editor_base );
        SetValue( editor.Text() );
        emit controller.RecordsChanged();
    } );

    text_editor->SetText( Value() );

    return text_editor;
}

C_ScriptRecordFactory::C_ScriptRecordFactory()
{
    m_RecordClass = "Script";
}

C_Record* C_ScriptRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_ScriptRecord* record = new C_ScriptRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_ScriptRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_ScriptRecord* record = new C_ScriptRecord( state, parent, root );
    return record;
}



