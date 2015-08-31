#include "FW/document.h"
#include "FW/RC/struct_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/PR/ui_record_name_property.h"

#include <QVBoxLayout>

#include <FW/UI/PR/ui_string_property.h>

C_StructRecord::C_StructRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Struct";
    m_Records = new C_RecordStruct( name, this );
}

C_StructRecord::C_StructRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Struct";
    m_Records = new C_RecordStruct( "", this );
    SetState( state, root );
}

C_StructRecord::~C_StructRecord()
{
    // void
}

QString C_StructRecord::Value()
{
    m_Value = QString::number( Records().Size() );
    return m_Value;
}

void C_StructRecord::SetValue( QString )
{
    qDebug() << "Setting Struct value is not allowed";
}


C_RecordStruct* C_StructRecord::Struct()
{
    return m_Records;
}

QStringList C_StructRecord::Html()
{
    QStringList html;

    for( C_Variant* variant : Records() )
        html << static_cast<C_Record*>( variant )->Html() ;

    return html;
}

QStringList C_StructRecord::Script()
{
    QStringList script;
    script << ( "\n" + FullName() + " = {} ;" );

    for( C_Variant* variant : Records() )
        script << static_cast<C_Record*>( variant )->Script() ;

    return script;
}

bool C_StructRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( Value() ); // VALUE NEEDS TO BE UPDATED , do not use m_Value
    row.append( m_Class );
    state.Read( row );

    for( C_Variant* variant : Records() )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        record->GetState( state );
    }

    return true;
}

bool C_StructRecord::SetState( C_StateWriter& state, C_RecordStruct* root )
{
    Records().Clear();

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2]; // GETTING PREVIOUS VALUE
    m_Class = row[3];

    Records().SetName( m_Name );
    long size = m_Value.toLong();

    for( long count = 0; count < size; ++count )
        Records().CreateRecord( state, -1, root );

    return true;
}

QWidget* C_StructRecord::PropertyWidget( C_Controller& controller )
{

    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( name_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

C_StructRecordFactory::C_StructRecordFactory()
{
    m_RecordClass = "Struct";
}

C_Record* C_StructRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root  )
{
    C_StructRecord* record = new C_StructRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_StructRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    C_StructRecord* record = new C_StructRecord( state, parent, root );
    return record;
}

