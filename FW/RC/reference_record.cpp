#include "FW/RC/reference_record.h"
#include "FW/UI/PR/ui_record_name_property.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QVBoxLayout>


TypeReferenceRecord::TypeReferenceRecord( QString id, QString name, QString value, TypeVariant* parent , TypeRecordStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Reference";
    m_Root = root;
}

TypeReferenceRecord::TypeReferenceRecord( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Reference";
    m_Root = root;
    SetState( state, root );
}

TypeReferenceRecord::~TypeReferenceRecord()
{
    // void
}

QWidget* TypeReferenceRecord::PropertyWidget( TypeController& controller )
{
    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new TypeUiRecordNameProperty( "Reference", Value(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
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

QString TypeReferenceRecord::Value()
{
    if( m_Value.isEmpty() )
        return "";

    TypeRecord* record = Referencee();

    if( record != 0 )
        return record->FullName();

    qDebug() << "Warning - Reference invalid:" << FullName();
    return "";
}

void TypeReferenceRecord::SetValue( QString full_name )
{
    TypeRecord* record =  Root().FromFullName( full_name );

    if( record != 0 )
    {
        m_Value = record->Id();
        return;
    }

    m_Value = "";
}

TypeRecord* TypeReferenceRecord::Referencee()
{
    return Root().FromId( m_Value, true );
}

bool TypeReferenceRecord::GetState( TypeStateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( m_Class );
    state.Read( row );

    return true;
}

bool TypeReferenceRecord::SetState( TypeStateWriter& state , TypeRecordStruct* root )
{
    m_Root = root;

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = TypeRecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
    m_Class = row[3];

    return true;
}

TypeReferenceRecordFactory::TypeReferenceRecordFactory()
{
    m_RecordClass = "Reference";
}

TypeRecord* TypeReferenceRecordFactory::CreateInstance( QString name, QString value, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeReferenceRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeReferenceRecordFactory::CreateInstance( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root )
{
    return new TypeReferenceRecord( state, parent, root );
}


