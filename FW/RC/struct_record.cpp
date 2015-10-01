//
// This file is polymorfic aware --

#include "FW/RC/struct_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include <QVBoxLayout>
#include <FW/UI/PR/ui_label_property.h>
#include <FW/UI/PR/ui_string_property.h>
#include "FW/tools.h"

TypeStructRecord::TypeStructRecord( QString id, QString name, QString value, TypeVariant* parent ):
    TypeRecord( id, name, value, parent )
{
    m_Class = "Struct";
    m_Struct = new TypeStruct( this );
}

TypeStructRecord::TypeStructRecord( TypeStateWriter& state, TypeVariant* parent ):
    TypeRecord( "", "", "", parent )
{
    m_Class = "Struct";
    m_Struct = new TypeStruct( this );
    SetState( state );
}

TypeStructRecord::~TypeStructRecord()
{
    // void
}

TypeStruct* TypeStructRecord::Struct() const
{
    return m_Struct;
}

void TypeStructRecord::Html(TypeHtmlBlockStream& block_stream , long role, TypeStruct& root )
{
    for( TypeVariantPtr<TypeRecord> record : *this->Struct() )
        record->Html( block_stream, role, root ) ;
}

bool TypeStructRecord::GetState( TypeStateReader& state )
{
    m_Value = QString::number( Struct()->Size() );

    QStringList row;
    row.append( this->Id() );
    row.append( this->Name() );
    row.append( this->Value() );
    row.append( this->Class() );
    row.append( QString::number( this->Flags() ) );
    state.Read( row );

    for( TypeVariantPtr<TypeRecord> record : *this->Struct() )
        record->GetState( state );

    return true;
}

bool TypeStructRecord::SetState( TypeStateWriter& state )
{
    m_Struct->Clear();

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = TypeRecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name      = row[1];
    m_Value     = row[2];
    m_Class     = row[3];
    m_Flags     = row[4].toLong();

    long size = m_Value.toLong();

    for( long count = 0; count < size; ++count )
        m_Struct->NewRecord( state, -1 );

    return true;
}

QWidget* TypeStructRecord::PropertyWidget( TypeController& controller )
{
    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", this->Class() );

    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", this->Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        this->SetName( property.Value() );
        emit controller.RecordChanged(this);
        emit controller.RecordChanged(/*generic slot*/);
        return true;
    } );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( class_widget );
    layout->addWidget( name_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

void TypeStructRecord::SetValue( const QString& value )
{
    qDebug() << "warning: setting struct value";
    m_Value = value;
}

const QString& TypeStructRecord::Value() const
{
    qDebug() << "warning: getting struct value";

    static QString tmp = QString::number( Struct()->Size() );
    return tmp;
}

QString& TypeStructRecord::Value()
{
    qDebug() << "warning: getting struct value";

    static QString tmp = QString::number( Struct()->Size() );
    return tmp;
}

TypeStructRecordFactory::TypeStructRecordFactory()
{
    m_RecordClass = "Struct";
}

TypeRecord* TypeStructRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent  )
{
    TypeStructRecord* record = new TypeStructRecord( TypeRecordFactory::GenerateId(), name, value, parent );
    return record;
}

TypeRecord* TypeStructRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent  )
{
    TypeStructRecord* record = new TypeStructRecord( state, parent );
    return record;
}

