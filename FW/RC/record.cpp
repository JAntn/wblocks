#include "FW/RC/record.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/UI/PR/ui_linetext_property.h"
#include <QVBoxLayout>
#include "FW/UI/ui_editor_container.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/BK/block_stream.h"
#include "FW/tools.h"

/////////////////////////////////////////////////////////////////////////////////
/// STATIC

long TypeRecordFactory::m_IdCount = 0;


QString TypeRecordFactory::GenerateId()
{
    return QString::number( m_IdCount++ );
}

QString TypeRecordFactory::IdCount()
{
    return QString::number( m_IdCount );
}

/////////////////////////////////////////////////////////////////////////////////
/// NON STATIC

TypeRecord::TypeRecord( QString id, QString name, QString value, TypeVariant* parent, TypeRecordStruct* ) :
    TypeVariant( parent ),
    m_Id( id ),
    m_Name( name ),
    m_Class( "Record" ),
    m_Value( value )
{
    SetFlags( FLAG_ACTION_ALL );
}

TypeRecord::TypeRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* ):
    TypeRecord( "", "", "", parent )
{
    SetState( state );
}

TypeRecord::~TypeRecord()
{
    // void
}

void TypeRecord::SetValue( QString value )
{
    m_Value = value;
}

QString TypeRecord::Value()
{
    return m_Value;
}


bool TypeRecord::GetState( TypeStateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( m_Class );
    state.Read( row );

    return true;
}

bool TypeRecord::SetState( TypeStateWriter& state, TypeRecordStruct* )
{
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

QWidget* TypeRecord::PropertyWidget( TypeController& controller )
{

    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new TypeUiLineTextProperty( "Value", Value(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiLineTextProperty&>( property_base );
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

TypeUiEditor* TypeRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    text_editor = new TypeUiTextEditor(
        id, Name(), Name().split( "." ).back(), 0/*parent widget*/,
        [&controller, this]( TypeUiEditor & editor_base )/*save callback*/
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        SetValue( editor->Text() );
        emit controller.RecordsChanged();
    } );

    text_editor->SetText( Value() );

    return text_editor;
}

TypeRecordStruct* TypeRecord::Struct()
{
    return 0;
}

void TypeRecord::Html( TypeBlockStream& )
{
    // void
}

void TypeRecord::Script( TypeBlockStream& )
{
    // void
}

QString TypeRecord::FullName() const
{
    auto* record_struct = static_cast<TypeRecordStruct*>( Parent() );

    if( record_struct->Name() != "root" )
    {
        TypeVariantPtr<TypeRecord> record( record_struct->Parent() );
        return record->FullName() + "." + Name();
    }

    return Name();
}

TypeRecordFactory::TypeRecordFactory() :
    m_RecordClass( "Record" )
{
    // void
}

TypeRecord* TypeRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeRecordStruct* root )
{
    return new TypeRecord( state, parent, root );
}






