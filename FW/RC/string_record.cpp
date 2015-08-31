#include "FW/RC/string_record.h"
#include "FW/UI/PR/ui_string_property.h"
#include "FW/UI/ui_main_window.h"
#include <FW/document.h>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/record.h"
#include <QHBoxLayout>
#include <FW/UI/PR/ui_record_name_property.h>

C_StringRecord::C_StringRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "String";
}

C_StringRecord::C_StringRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root  ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "String";
    SetState( state, root );
}

C_StringRecord::~C_StringRecord()
{
    //void
}

QWidget* C_StringRecord::PropertyWidget( C_Controller& controller )
{

    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new C_UiStringProperty( "String", Value(), [&controller, this]( C_UiProperty & property_base )
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

C_StringRecordFactory::C_StringRecordFactory()
{
    m_RecordClass = "String";
}

C_Record* C_StringRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_StringRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_StringRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_StringRecord( state, parent, root );
}

