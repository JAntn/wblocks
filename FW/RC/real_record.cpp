
#include "FW/RC/real_record.h"
#include "FW/UI/PR/ui_real_property.h"
#include "FW/UI/PR/ui_record_name_property.h"
#include <QVBoxLayout>

#include "FW/UI/ui_main_window.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"

C_RealRecord::C_RealRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Real";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

C_RealRecord::C_RealRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Real";
    SetState( state, root );
}

C_RealRecord::~C_RealRecord()
{
    //void
}

QWidget* C_RealRecord::PropertyWidget( C_Controller& controller )
{
    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new C_UiRealProperty( "Real", Value().toDouble(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRealProperty&>( property_base );
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

C_RealRecordFactory::C_RealRecordFactory()
{
    m_RecordClass = "Real";
}

C_Record* C_RealRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    C_RealRecord* record = new C_RealRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_RealRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    C_RealRecord* record = new C_RealRecord( state, parent, root );
    return record;
}




