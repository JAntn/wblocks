#include "FW/RC/struct_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include <QVBoxLayout>
#include <FW/UI/PR/ui_label_property.h>
#include <FW/UI/PR/ui_string_property.h>
#include "FW/tools.h"

TypeStructRecord::TypeStructRecord( QString id, QString name, QString value, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Struct";
    m_Struct = new TypeStruct( this );
}

TypeStructRecord::TypeStructRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Struct";
    m_Struct = new TypeStruct( this );
    SetState( state, root );
}

TypeStructRecord::~TypeStructRecord()
{
    // void
}

QString TypeStructRecord::Value()
{
    m_Value = QString::number( Struct()->Size() );
    return m_Value;
}

void TypeStructRecord::SetValue( QString )
{
    qDebug() << "Setting Struct value is not allowed";
}


TypeStruct* TypeStructRecord::Struct()
{
    return m_Struct;
}

void TypeStructRecord::Html( TypeHtmlBlockStream& block_stream )
{
    for( TypeVariantPtr<TypeRecord> record : *Struct() )
        record->Html( block_stream ) ;
}

void TypeStructRecord::Script( TypeHtmlBlockStream& block_stream )
{
    block_stream.Append( "\n" + FullName() + " = {} ;", Id() );

    for( TypeVariantPtr<TypeRecord> record : *Struct() )
        record->Script( block_stream ) ;
}

bool TypeStructRecord::GetState( TypeStateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( Value() ); // VALUE NEEDS TO BE UPDATED , do not use m_Value
    row.append( m_Class );
    state.Read( row );

    for( TypeVariantPtr<TypeRecord> record : *Struct() )
        record->GetState( state );

    return true;
}

bool TypeStructRecord::SetState( TypeStateWriter& state, TypeStruct* root )
{
    Struct()->Clear();

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = TypeRecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2]; // GETTING PREVIOUS VALUE
    m_Class = row[3];

    long size = m_Value.toLong();

    for( long count = 0; count < size; ++count )
        Struct()->NewRecord( state, -1, root );

    return true;
}

QWidget* TypeStructRecord::PropertyWidget( TypeController& controller )
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

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( class_widget );
    layout->addWidget( name_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

TypeStructRecordFactory::TypeStructRecordFactory()
{
    m_RecordClass = "Struct";
}

TypeRecord* TypeStructRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root  )
{
    TypeStructRecord* record = new TypeStructRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

TypeRecord* TypeStructRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    TypeStructRecord* record = new TypeStructRecord( state, parent, root );
    return record;
}

