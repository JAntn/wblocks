#include "FW/RC/string_record.h"
#include "FW/UI/PR/ui_string_property.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/record.h"
#include <QHBoxLayout>
#include <FW/UI/PR/ui_recordname_property.h>

TypeStringRecord::TypeStringRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "String";
}

TypeStringRecord::TypeStringRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root  ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "String";
    SetState( state, root );
}

TypeStringRecord::~TypeStringRecord()
{
    //void
}

QWidget* TypeStringRecord::PropertyWidget( TypeController& controller )
{

    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new TypeUiStringProperty( "String", Value(), [&controller, this]( TypeUiProperty & property_base )
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

TypeStringRecordFactory::TypeStringRecordFactory()
{
    m_RecordClass = "String";
}

TypeRecord* TypeStringRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeStringRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeStringRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeStringRecord( state, parent, root );
}

