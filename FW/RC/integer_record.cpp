#include "FW/RC/integer_record.h"
#include "FW/UI/PR/ui_integer_property.h"
#include "FW/UI/PR/ui_record_name_property.h"
#include <QVBoxLayout>
#include <FW/ST/state_writer.h>
#include <FW/ST/state_reader.h>


TypeIntegerRecord::TypeIntegerRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Integer";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

TypeIntegerRecord::TypeIntegerRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
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
    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();
    } );


    QWidget* value_widget;

    value_widget = new TypeUiIntegerProperty( "Integer", Value().toLong(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiIntegerProperty&>( property_base );
        SetValue( QString::number( property.Value() ) );
        emit controller.RecordsChanged();
    } );

    QVBoxLayout* layout = new QVBoxLayout;
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

TypeRecord* TypeIntegerRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeIntegerRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeIntegerRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeIntegerRecord( state, parent, root );
}





