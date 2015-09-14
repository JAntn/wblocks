//
// - This file is polimorfic aware.

#include "FW/BK/html_block_stream.h"
#include "FW/RC/bool_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/PR/ui_property.h"
#include "FW/UI/PR/ui_label_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/UI/PR/ui_bool_property.h"
#include "FW/UI/PR/ui_combo_property.h"

#include <QHBoxLayout>

TypeBoolRecord::TypeBoolRecord( QString id, QString name, QString value, TypeVariant* parent , TypeStruct* root ):
    TypeRecord( id, name, value, parent, root )
{
    m_Class = "Bool" ;

    if( m_Value.isEmpty() )
        m_Value = "False";

    m_HtmlAction = HTML_ACTION_AUTO;
}

TypeBoolRecord::TypeBoolRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeRecord( "", "", "", parent, root )
{
    m_Class = "Bool" ;
    SetState( state, root );
}

TypeBoolRecord::~TypeBoolRecord()
{
    //void
}

bool TypeBoolRecord::GetState( TypeStateReader& state )
{
    //
    // Store the file name to a state object:

    QStringList row;
    row.append( this->Id() );
    row.append( this->Name() );
    row.append( this->Value() );
    row.append( this->Class() );
    state.Read( row );

    //
    // Store the html action to a state object:

    row.clear();
    row.append( "NONE" );
    row.append( "HTML_ACTION" );
    row.append( QString::number( this->HtmlAction() ) );
    row.append( "NONE" );
    state.Read( row );

    return true;
}

bool TypeBoolRecord::SetState( TypeStateWriter& state, TypeStruct* )
{
    //
    // Take the file name from state object:

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = TypeRecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
    m_Class = row[3];

    //
    // Take the html action from state object:

    row.clear();
    state.Write( row );
    m_HtmlAction = row[2].toInt();

    return true;
}

QWidget* TypeBoolRecord::PropertyWidget( TypeController& controller )
{

    //
    // This property shows class name:

    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", this->Class() );

    //
    // This property selects record name:

    QWidget* name_widget;
    name_widget = new TypeUiRecordNameProperty( "Name", this->Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        this->SetName( property.Value() );
        emit controller.RecordsChanged();
        return true;
    } );

    //
    // This property selects boolean value:

    QWidget* value_widget;

    value_widget = new TypeUiBoolProperty(
        "Bool",
        ( this->Value() == "True" ) ? true : false,
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiBoolProperty&>( property_base );
        this->SetValue( property.Value() ? "True" : "False" );
        emit controller.RecordsChanged();
        return true;
    } );


    //
    // This property selects which action to do when html code is buildig:

    QWidget* combo_html_widget;

    combo_html_widget = new TypeUiComboProperty(
        "Html", 0,
        QStringList{ "Auto", "Inline", "Java Script", "Java Script Block", "Main Java Script Block", "None" },
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiComboProperty&>( property_base );

        //
        // Map selected combo box value to an html action:

        if( property.Value() == 0 )
            this->SetHtmlAction( HTML_ACTION_AUTO );

        else if( property.Value() == 1 )
            this->SetHtmlAction( HTML_ACTION_INLINE );

        else if( property.Value() == 2 )
            this->SetHtmlAction( HTML_ACTION_JAVASCRIPT );

        else if( property.Value() == 3 )
            this->SetHtmlAction( HTML_ACTION_JAVASCRIPT_BLOCK );

        else if( property.Value() == 4 )
            this->SetHtmlAction( HTML_ACTION_MAIN_JAVASCRIPT_BLOCK );

        else if( property.Value() == 5 )
            this->SetHtmlAction( HTML_ACTION_NONE );

        emit controller.RecordsChanged();

        return true;
    } );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( class_widget );
    layout->addWidget( name_widget );
    layout->addWidget( value_widget );
    layout->addWidget( combo_html_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

void TypeBoolRecord::Html( TypeHtmlBlockStream& block_stream )
{
    //
    // Generate an html block depending on selected html related action:

    int action = this->HtmlAction();

    if( ( action == HTML_ACTION_INLINE)  )
    {
        block_stream.Append( this->Value(), this->Id() );
    }

    else if( ( action == HTML_ACTION_JAVASCRIPT )  )
    {
        QString script_txt = "\n" + this->FullName() + " = " + this->Value() + ";";
        block_stream.Append( script_txt, this->Id() );
    }

    else if( action == HTML_ACTION_JAVASCRIPT_BLOCK )
    {
        QStringList html;
        QString script_txt = "\n" + this->FullName() + " = " + this->Value() + ";";
        html << "\n<script>" << script_txt << "</script>";
        block_stream.Append( html.join( "" ), this->Id() );
    }

}

void TypeBoolRecord::Script( TypeHtmlBlockStream& block_stream )
{
    //
    // Generate a Java Script variable:

    int action = this->HtmlAction();

    if( ( action == HTML_ACTION_MAIN_JAVASCRIPT_BLOCK ) || ( action == HTML_ACTION_AUTO ) )
    {
        QString script_txt = "\n" + this->FullName() + " = " + this->Value() + ";";
        block_stream.Append( script_txt, this->Id() );
    }

}

TypeBoolRecordFactory::TypeBoolRecordFactory()
{
    m_RecordClass = "Bool";
}

TypeRecord* TypeBoolRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeBoolRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeBoolRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeBoolRecord( state, parent, root );
}




