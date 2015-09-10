#include "FW/RC/real_record.h"
#include "FW/UI/PR/ui_real_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include <QVBoxLayout>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <FW/UI/PR/ui_label_property.h>

TypeRealRecord::TypeRealRecord( QString id, QString name, QString value, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Real";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

TypeRealRecord::TypeRealRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Real";
    SetState( state, root );
}

TypeRealRecord::~TypeRealRecord()
{
    //void
}

QWidget* TypeRealRecord::PropertyWidget( TypeController& controller )
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

    value_widget = new TypeUiRealProperty( "Real", Value().toDouble(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRealProperty&>( property_base );
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

TypeRealRecordFactory::TypeRealRecordFactory()
{
    m_RecordClass = "Real";
}

TypeRecord* TypeRealRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeStruct* root )
{
    TypeRealRecord* record = new TypeRealRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

TypeRecord* TypeRealRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    TypeRealRecord* record = new TypeRealRecord( state, parent, root );
    return record;
}




