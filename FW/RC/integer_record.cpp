#include "FW/RC/integer_record.h"
#include "FW/UI/PR/ui_integer_property.h"
#include "FW/UI/PR/ui_record_name_property.h"
#include <QVBoxLayout>

#include "FW/UI/ui_main_window.h"
#include <FW/ST/state_writer.h>
#include <FW/ST/state_reader.h>
#include <FW/document.h>


C_IntegerRecord::C_IntegerRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Integer";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

C_IntegerRecord::C_IntegerRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Integer";
    SetState( state, root );
}

C_IntegerRecord::~C_IntegerRecord()
{
    // void
}

QWidget* C_IntegerRecord::PropertyWidget( C_Controller& controller )
{
    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();
    } );


    QWidget* value_widget;

    value_widget = new C_UiIntegerProperty( "Integer", Value().toLong(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiIntegerProperty&>( property_base );
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

C_IntegerRecordFactory::C_IntegerRecordFactory()
{
    m_RecordClass = "Integer";
}

C_Record* C_IntegerRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_IntegerRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_IntegerRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_IntegerRecord( state, parent, root );
}





