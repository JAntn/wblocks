#include "FW/RC/file_record.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QVBoxLayout>
#include <FW/UI/PR/ui_label_property.h>


TypeFileRecord::TypeFileRecord( QString id, QString name, QString value, TypeVariant* parent , TypeStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "File";

    if( m_Value.isEmpty() )
        m_Value = "untitled";
}

TypeFileRecord::TypeFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
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

    value_widget = new TypeUiFileProperty( "File", Value(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiFileProperty&>( property_base );
        SetValue( property.Value() );
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

TypeRecord* TypeFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeFileRecord( state, parent, root );
}

TypeFileRecordFactory::TypeFileRecordFactory()
{
    m_RecordClass = "File";
}


