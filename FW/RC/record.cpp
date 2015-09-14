//
// - This file is polimorfic aware.

#include "FW/RC/record.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/UI/PR/ui_linetext_property.h"
#include "FW/UI/PR/ui_label_property.h"
#include <QVBoxLayout>
#include "FW/UI/ui_editor_container.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/BK/html_block_stream.h"
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

TypeRecord::TypeRecord( QString id, QString name, QString value, TypeVariant* parent, TypeStruct* ) :
    TypeVariant( parent ),
    m_Id( id ),
    m_Name( name ),
    m_Class( "Record" ),
    m_Value( value )
{
    SetFlags( FLAG_ACTION_ALL );
}

TypeRecord::TypeRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* ):
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
    row.append( this->Id() );
    row.append( this->Name() );
    row.append( this->Value() );
    row.append( this->Class() );
    state.Read( row );

    return true;
}

bool TypeRecord::SetState( TypeStateWriter& state, TypeStruct* )
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

    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", this->Class() );

    QWidget* name_widget;
    name_widget = new TypeUiRecordNameProperty(
        "Name",
        this->Name(),
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        this->SetName( property.Value() );
        emit controller.RecordsChanged();
        return true;
    } );

    QWidget* value_widget;
    value_widget = new TypeUiLineTextProperty(
        "Value",
        this->Value(),
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiLineTextProperty&>( property_base );
        this->SetValue( property.Value() );
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

TypeUiEditor* TypeRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    text_editor = new TypeUiTextEditor(
        id, this->Name(), this->Name().split( "." ).back(), 0/*parent widget*/,
        [&controller, this]( TypeUiEditor & editor_base )/*save callback*/
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        this->SetValue( editor->Text() );
        emit controller.RecordsChanged();
        return true;
    } );

    text_editor->SetText( this->Value() );
    text_editor->SetHasChanged( false );

    return text_editor;
}

TypeStruct* TypeRecord::Struct()
{
    return 0;
}

TypeStruct* TypeRecord::ParentStruct()
{
    return TypeVariantPtr<TypeStruct>( this->Parent() );
}

TypeRecord* TypeRecord::ParentRecord()
{
    TypeStruct* parent_struct = this->ParentStruct();

    if( parent_struct != 0 )
        return parent_struct->ParentRecord();

    return 0;
}

void TypeRecord::Html( TypeHtmlBlockStream& )
{
    // void
}

void TypeRecord::Script( TypeHtmlBlockStream& )
{
    // void
}

QString TypeRecord::FullName()
{
    TypeRecord* parent_record = this->ParentRecord();

    if( parent_record != 0 )
        return parent_record->FullName() + "." + this->Name();

    return this->Name();
}

TypeRecordFactory::TypeRecordFactory() :
    m_RecordClass( "Record" )
{
    // void
}

TypeRecord* TypeRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent , TypeStruct* root )
{
    return new TypeRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent , TypeStruct* root )
{
    return new TypeRecord( state, parent, root );
}






