#include "FW/RC/bool_record.h"
#include "FW/UI/PR/ui_bool_property.h"
#include "FW/UI/PR/ui_record_name_property.h"

#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#include <QVBoxLayout>

C_BoolRecord::C_BoolRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Bool";

    if( m_Value.isEmpty() )
        m_Value = "False";
}

C_BoolRecord::C_BoolRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Bool";

    SetState( state, root );
}

C_BoolRecord::~C_BoolRecord()
{
    // void
}

QWidget* C_BoolRecord::PropertyWidget( C_Controller& controller )
{

    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new C_UiBoolProperty(
        "Bool",
        ( Value() == "True" ) ? true : false,
        [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiBoolProperty&>( property_base );
        SetValue( property.Value() ? "True" : "False" );
        emit controller.RecordsChanged();
    } );


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( name_widget );
    layout->addWidget( value_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

C_BoolRecordFactory::C_BoolRecordFactory()
{
    m_RecordClass = "Bool";
}

C_Record* C_BoolRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_BoolRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_BoolRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_BoolRecord( state, parent, root );
}





