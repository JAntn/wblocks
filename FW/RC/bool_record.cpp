#include "FW/RC/bool_record.h"
#include "FW/UI/PR/ui_bool_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QVBoxLayout>
#include <FW/UI/PR/ui_label_property.h>

TypeBoolRecord::TypeBoolRecord( QString id, QString name, QString value, TypeVariant* parent , TypeStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Bool";

    if( m_Value.isEmpty() )
        m_Value = "False";
}

TypeBoolRecord::TypeBoolRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Bool";

    SetState( state, root );
}

TypeBoolRecord::~TypeBoolRecord()
{
    // void
}

QWidget* TypeBoolRecord::PropertyWidget( TypeController& controller )
{

    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", Class() );

    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();
        return true;
    } );

    QWidget* value_widget;

    value_widget = new TypeUiBoolProperty(
        "Bool",
        ( Value() == "True" ) ? true : false,
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiBoolProperty&>( property_base );
        SetValue( property.Value() ? "True" : "False" );
        emit controller.RecordsChanged();
        return true;
    } );


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( class_widget );
    layout->addWidget( name_widget );
    layout->addWidget( value_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

TypeBoolRecordFactory::TypeBoolRecordFactory()
{
    m_RecordClass = "Bool";
}

TypeRecord* TypeBoolRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeBoolRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeBoolRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeBoolRecord( state, parent, root );
}





