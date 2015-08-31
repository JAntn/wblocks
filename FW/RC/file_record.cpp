#include "FW/RC/file_record.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/PR/ui_record_name_property.h"

#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#include <QVBoxLayout>



C_FileRecord::C_FileRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "File";

    if( m_Value.isEmpty() )
        m_Value = "untitled";
}

C_FileRecord::C_FileRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "File";
    SetState( state, root );
}

C_FileRecord::~C_FileRecord()
{
    //void
}

QWidget* C_FileRecord::PropertyWidget( C_Controller& controller )
{
    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();
    } );

    QWidget* value_widget;

    value_widget = new C_UiFileProperty( "File", Value(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiFileProperty&>( property_base );
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

QString C_FileRecord::FilePath()
{
    QStringList string_list = Value().split( "/" );
    string_list.pop_back();
    return string_list.join( "/" );
}

QString C_FileRecord::FileName()
{
    return Value().split( "/" ).back();
}

QString C_FileRecord::FileFullName()
{
    return Value();
}

C_Record* C_FileRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_FileRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_FileRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_FileRecord( state, parent, root );
}

C_FileRecordFactory::C_FileRecordFactory()
{
    m_RecordClass = "File";
}


