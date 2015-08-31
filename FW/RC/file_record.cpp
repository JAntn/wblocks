#include "FW/RC/file_record.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/PR/ui_record_name_property.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QVBoxLayout>


TypeFileRecord::TypeFileRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "File";

    if( m_Value.isEmpty() )
        m_Value = "untitled";
}

TypeFileRecord::TypeFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "File";
    SetState( state, root );
}

TypeFileRecord::~TypeFileRecord()
{
    //void
}

QWidget* TypeFileRecord::PropertyWidget( TypeController& controller )
{
    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();
    } );

    QWidget* value_widget;

    value_widget = new TypeUiFileProperty( "File", Value(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiFileProperty&>( property_base );
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

QString TypeFileRecord::FilePath()
{
    QStringList string_list = Value().split( "/" );
    string_list.pop_back();
    return string_list.join( "/" );
}

QString TypeFileRecord::FileName()
{
    return Value().split( "/" ).back();
}

QString TypeFileRecord::FileFullName()
{
    return Value();
}

TypeRecord* TypeFileRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeFileRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeFileRecord( state, parent, root );
}

TypeFileRecordFactory::TypeFileRecordFactory()
{
    m_RecordClass = "File";
}


