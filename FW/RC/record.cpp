#include "FW/RC/record.h"
#include "FW/UI/PR/ui_record_name_property.h"
#include "FW/UI/PR/ui_line_text_property.h"
#include <QVBoxLayout>


#include <QCoreApplication>
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/document.h"

#include "FW/UI/ui_main_window.h"

#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"



/////////////////////////////////////////////////////////////////////////////////
/// STATIC

long C_RecordFactory::m_IdCount = 0;


QString C_RecordFactory::GenerateId()
{
    return QString::number( m_IdCount++ );
}

QString C_RecordFactory::IdCount()
{
    return QString::number( m_IdCount );
}

/////////////////////////////////////////////////////////////////////////////////
/// NON STATIC

C_Record::C_Record( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* ) :
    C_Variant( parent ),
    m_Id( id ),
    m_Name( name ),
    m_Class( "Record" ),
    m_Value( value )
{
    SetFlags( FLAG_ACTION_ALL );
}

C_Record::C_Record( C_StateWriter& state, C_Variant* parent, C_RecordStruct* ):
    C_Record( "", "", "", parent )
{
    SetState( state );
}

C_Record::~C_Record()
{
    // void
}

void C_Record::SetValue( QString value )
{
    m_Value = value;
}

QString C_Record::Value()
{
    return m_Value;
}


bool C_Record::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( m_Class );
    state.Read( row );

    return true;
}

bool C_Record::SetState( C_StateWriter& state, C_RecordStruct* )
{
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

QWidget* C_Record::PropertyWidget( C_Controller& controller )
{

    QWidget* name_widget;

    name_widget = new C_UiRecordNameProperty( "Name", Name(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiRecordNameProperty&>( property_base );
        SetName( property.Value() );
        emit controller.RecordsChanged();

    } );

    QWidget* value_widget;

    value_widget = new C_UiLineTextProperty( "Value", Value(), [&controller, this]( C_UiProperty & property_base )
    {
        auto& property = static_cast<C_UiLineTextProperty&>( property_base );
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

C_UiEditor* C_Record::EditorWidget( QString id, C_Controller& controller )
{
    C_UiTextEditor* text_editor;

    text_editor = new C_UiTextEditor( id, Name(), Name().split( "." ).back(), [&controller, this]( C_UiEditor & editor_base )
    {
        C_UiTextEditor& editor = static_cast<C_UiTextEditor&>( editor_base );
        SetValue( editor.Text() );
        emit controller.RecordsChanged();
    } );

    text_editor->SetText( Value() );

    return text_editor;
}

C_RecordStruct* C_Record::Struct()
{
    return 0;
}

QStringList C_Record::Script()
{
    return QStringList();
}

QStringList C_Record::Html()
{
    return QStringList();
}

QString C_Record::FullName() const
{
    auto* record_struct = static_cast<C_RecordStruct*>( Parent() );

    if( record_struct->Name() != "root" )
    {
        C_Record* record = static_cast<C_Record*>( record_struct->Parent() );
        return record->FullName() + "." + Name();
    }

    return Name();
}

C_RecordFactory::C_RecordFactory() :
    m_RecordClass( "Record" )
{
    // void
}

C_Record* C_RecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_Record( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_RecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_Record( state, parent, root );
}






