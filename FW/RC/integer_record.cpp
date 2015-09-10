#include "FW/RC/integer_record.h"
#include "FW/UI/PR/ui_integer_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include <QVBoxLayout>
#include <FW/ST/state_writer.h>
#include <FW/ST/state_reader.h>
#include <FW/UI/PR/ui_label_property.h>


TypeIntegerRecord::TypeIntegerRecord( QString id, QString name, QString value, TypeVariant* parent , TypeStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Integer";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

TypeIntegerRecord::TypeIntegerRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Integer";
    SetState( state, root );
}

TypeIntegerRecord::~TypeIntegerRecord()
{
    // void
}

QWidget* TypeIntegerRecord::PropertyWidget( TypeController& controller )
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

    value_widget = new TypeUiIntegerProperty( "Integer", Value().toLong(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiIntegerProperty&>( property_base );
        SetValue( QString::number( property.Value() ) );
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

TypeIntegerRecordFactory::TypeIntegerRecordFactory()
{
    m_RecordClass = "Integer";
}

TypeRecord* TypeIntegerRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeStruct* root )
{
    return new TypeIntegerRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeIntegerRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    return new TypeIntegerRecord( state, parent, root );
}





