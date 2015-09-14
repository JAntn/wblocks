//
// - This file is polymorfic aware.

#include "FW/tools.h"
#include "FW/RC/JS/js_script_file_record.h"
#include "FW/BK/html_block_stream.h"
#include "FW/UI/PR/ui_combo_property.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/PR/ui_label_property.h"
#include "FW/UI/PR/ui_recordname_property.h"

#include <QCoreApplication>
#include <QVBoxLayout>



TypeJsScriptFileRecord::TypeJsScriptFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeStruct* root ):
    TypeTextFileRecord( id, name, value, parent, root )
{
    m_Class = "JsScriptFile";
    m_HtmlAction = HTML_ACTION_AUTO;

}

TypeJsScriptFileRecord::TypeJsScriptFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeTextFileRecord( "", "", "", parent, root )
{
    m_Class = "JsScriptFile";
    SetState( state, root );
}

TypeJsScriptFileRecord::~TypeJsScriptFileRecord()
{
    // void
}

QString TypeJsScriptFileRecord::FileFormatTitle()
{
    //
    // Used in QFileDialog:

    return QCoreApplication::translate( "TypeJsScriptFileRecord", "Java Script" );
}

QString TypeJsScriptFileRecord::FileFormat()
{
    //
    // Used in QFileDialog and editor Id generation:

    return "JAVASCRIPT";
}

QString TypeJsScriptFileRecord::FileExtension()
{
    //
    // Used in QFileDialog:

    return "(*.js)";
}

void TypeJsScriptFileRecord::Script( TypeHtmlBlockStream& block_stream )
{
    //
    // Generate an html block at main script block:

    if(  this->HtmlAction() == HTML_ACTION_MAIN_JAVASCRIPT_BLOCK  )
        block_stream.Append(
            TypeController::LoadTextFile( this->FileFullName() ), this->Id() );
}

void TypeJsScriptFileRecord::Html( TypeHtmlBlockStream& block_stream )
{
    //
    // Generate an html block depending on selected html related action:

    int action = this->HtmlAction();

    if( action == HTML_ACTION_JAVASCRIPT_BLOCK )
    {
        QStringList html;
        html << "\n<script type=\"text\\javascript\" src=\"" << this->FileFullName() << "\"></script>";
        block_stream.Append( html.join( "" ), this->Id() );
    }
    else if( ( action == HTML_ACTION_INLINE ) || ( action == HTML_ACTION_AUTO ) )
    {
        block_stream.Append(
            TypeController::LoadTextFile( this->FileFullName() ), this->Id() );
    }
}

QWidget* TypeJsScriptFileRecord::PropertyWidget( TypeController& controller )
{
    //
    // This property shows the record's class:

    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", this->Class() );

    //
    // This property sets the record's name:

    QWidget* name_widget;

    name_widget = new TypeUiRecordNameProperty( "Name", this->Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiRecordNameProperty&>( property_base );
        this->SetName( property.Value() );
        emit controller.RecordsChanged();
        return true;
    } );

    //
    // This property selects the text file:

    QWidget* value_widget;

    value_widget = new TypeUiFileProperty(
        "File",
        this->FileFullName(),
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiFileProperty&>( property_base );
        this->SetFileFullName( property.Value() );
        emit controller.RecordsChanged();
        return true;
    } );

    //
    // This property selects which action to do when html code is buildig:

    QWidget* combo_html_widget;

    combo_html_widget = new TypeUiComboProperty(
        "Html", 0,
        QStringList{ "Auto", "Inline", "Java Script Block", "Main Java Script Block", "None", },
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
            this->SetHtmlAction( HTML_ACTION_JAVASCRIPT_BLOCK );

        else if( property.Value() == 3 )
            this->SetHtmlAction( HTML_ACTION_MAIN_JAVASCRIPT_BLOCK );

        else if( property.Value() == 4 )
            this->SetHtmlAction( HTML_ACTION_NONE );

        emit controller.RecordsChanged();

        return true;
    } );

    //
    // Append all property widgets to layout:

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( class_widget );
    layout->addWidget( name_widget );
    layout->addWidget( value_widget );
    layout->addWidget( combo_html_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}

TypeJsScriptFileRecordFactory::TypeJsScriptFileRecordFactory()
{
    m_RecordClass = "JsScriptFile";
}

TypeRecord* TypeJsScriptFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeJsScriptFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeJsScriptFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeJsScriptFileRecord( state, parent, root );
}



