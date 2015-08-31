#include "FW/RC/reference_record.h"
#include "FW/UI/PR/ui_record_name_property.h"

#include "FW/UI/ui_main_window.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"

#include <QVBoxLayout>


C_ReferenceRecord::C_ReferenceRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Reference";
    m_Root = root;
}

C_ReferenceRecord::C_ReferenceRecord( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Reference";
    m_Root = root;
    SetState( state, root );
}

C_ReferenceRecord::~C_ReferenceRecord()
{
    // void
}

QWidget* C_ReferenceRecord::PropertyWidget( C_Controller& controller )
{
    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new C_UiRecordNameProperty( "Reference", Value(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
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

QString C_ReferenceRecord::Value()
{
    if( m_Value.isEmpty() )
        return "";

    C_Record* record = Referencee();

    if( record != 0 )
        return record->FullName();

    qDebug() << "Warning - Reference invalid:" << FullName();
    return "";
}

void C_ReferenceRecord::SetValue( QString full_name )
{
    C_Record* record =  Root().FromFullName( full_name );

    if( record != 0 )
    {
        m_Value = record->Id();
        return;
    }

    m_Value = "";
}

C_Record* C_ReferenceRecord::Referencee()
{
    return Root().FromId( m_Value, true );
}

bool C_ReferenceRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( m_Class );
    state.Read( row );

    return true;
}

bool C_ReferenceRecord::SetState( C_StateWriter& state , C_RecordStruct* root )
{
    m_Root = root;

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
    m_Class = row[3];

    return true;
}

C_ReferenceRecordFactory::C_ReferenceRecordFactory()
{
    m_RecordClass = "Reference";
}

C_Record* C_ReferenceRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_ReferenceRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_ReferenceRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_ReferenceRecord( state, parent, root );
}


