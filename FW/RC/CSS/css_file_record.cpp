//
// - This file is polymorfic aware.

#include "FW/tools.h"
#include "FW/RC/CSS/css_file_record.h"
#include "FW/BK/html_block_stream.h"
#include "FW/UI/PR/ui_combo_property.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/PR/ui_label_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include <QCoreApplication>
#include <QVBoxLayout>


TypeCssFileRecord::TypeCssFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeStruct* root ):
    TypeTextFileRecord( id, name, value, parent, root )
{
    m_Class = "CssFile";
    m_HtmlAction = HTML_ACTION_AUTO;
}

TypeCssFileRecord::TypeCssFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeTextFileRecord( "", "", "", parent, root )
{
    m_Class = "CssFile";
    SetState( state, root );
}

TypeCssFileRecord::~TypeCssFileRecord()
{
    // void
}

QString TypeCssFileRecord::FileFormatTitle()
{
    //
    // Used in QFileDialog:

    return QCoreApplication::translate( "TypeCssFileRecord", "Css" );
}

QString TypeCssFileRecord::FileFormat()
{
    //
    // Used in QFileDialog and editor Id:

    return "CSS";
}

QString TypeCssFileRecord::FileExtension()
{
    //
    // Used in QFileDialog:

    return "(*.css)";
}

void TypeCssFileRecord::Html( TypeHtmlBlockStream& block_stream )
{
    //
    // Generate an html block depending on selected html related action:

    int action = this->HtmlAction();

    if( ( action == HTML_ACTION_INLINE ) || ( action == HTML_ACTION_AUTO ) )
        block_stream.Append(
            TypeController::LoadTextFile( this->FileFullName() ),
            this->Id() );

    else if( action == HTML_ACTION_CSS_BLOCK )
        block_stream.Append(
            "<style>" + TypeController::LoadTextFile( this->FileFullName() ) + "</style>",
            this->Id() );
}


QWidget* TypeCssFileRecord::PropertyWidget( TypeController& controller )
{
    //
    // This property shows the record's class:

    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", this->Class() );

    //
    // This property sets the record's name:

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
        QStringList{ "Auto", "Inline", "Css Block", "None"},
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
            this->SetHtmlAction( HTML_ACTION_CSS_BLOCK );

        else if( property.Value() == 3 )
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

TypeCssFileRecordFactory::TypeCssFileRecordFactory()
{
    m_RecordClass = "CssFile";
}

TypeRecord* TypeCssFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeCssFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeCssFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeCssFileRecord( state, parent, root );
}


