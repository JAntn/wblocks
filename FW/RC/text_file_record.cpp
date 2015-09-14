//
// - This file is polymorfic aware.

#include "FW/tools.h"
#include "FW/RC/text_file_record.h"
#include "FW/RC/struct.h"
#include "FW/RC/file_record.h"
#include "FW/UI/PR/ui_file_property.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/BK/html_block_stream.h"
#include "FW/UI/SH/ui_syntax_highlighter_factory.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/PR/ui_combo_property.h"
#include "FW/UI/PR/ui_label_property.h"
#include "FW/UI/PR/ui_recordname_property.h"
#include <QCoreApplication>
#include <QVBoxLayout>


TypeTextFileRecord::TypeTextFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeStruct* root ):
    TypeFileRecord( id, name, value, parent, root )
{
    m_Class = "TextFile";
    m_HtmlAction = HTML_ACTION_AUTO;
}

TypeTextFileRecord::TypeTextFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeFileRecord( "", "", "", parent, root )
{
    m_Class = "TextFile";
    SetState( state, root );
}

TypeTextFileRecord::~TypeTextFileRecord()
{
    // void
}

QString TypeTextFileRecord::FileFormatTitle()
{
    //
    // Used in QFileDialog:

    return QCoreApplication::translate( "TypeTextFileRecord", "Plain Text" );
}

QString TypeTextFileRecord::FileFormat()
{
    //
    // Used in QFileDialog and editor Id generator:

    return "PLAINTEXT";
}

QString TypeTextFileRecord::FileExtension()
{
    //
    // Used in QFileDialog:

    return "(*.txt)";
}

void TypeTextFileRecord::Html( TypeHtmlBlockStream& block_stream )
{
    //
    // Generate an html block depending on selected html related action:

    int action = this->HtmlAction();

    if( ( action == HTML_ACTION_INLINE ) || ( action == HTML_ACTION_AUTO ) )
        block_stream.Append( TypeController::LoadTextFile( this->Value() ), this->Id() );
}

bool TypeTextFileRecord::GetState( TypeStateReader& state )
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

bool TypeTextFileRecord::SetState( TypeStateWriter& state, TypeStruct* )
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

QWidget* TypeTextFileRecord::PropertyWidget( TypeController& controller )
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
        this->Value(),
        [&controller, this]( TypeUiProperty & property_base )
    {
        auto& property = static_cast<TypeUiFileProperty&>( property_base );
        this->SetValue( property.Value() );
        emit controller.RecordsChanged();

        return true;
    } );

    //
    // This property selects which action to do when html code is buildig:

    QWidget* combo_html_widget;

    combo_html_widget = new TypeUiComboProperty(
        "Html", 0,
        QStringList{ "Auto", "Inline", "None"},
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

TypeUiEditor* TypeTextFileRecord::EditorWidget( QString id, TypeController& controller )
{
    TypeUiTextEditor* text_editor;

    //
    // Select the syntax highlighter in accordance to file format:

    TypeUiSyntaxHighlighter* syntax_highlighter =
        controller.SyntaxHighlighterFactory().NewInstance(
            this->FileFormat() );

    //
    // Callback to save file contents:

    TypeUiEditor::TypeSaveCallback save_callback =
        [&controller, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        TypeController::SaveTextFile( this->FileFullName(), editor->Text() );
        emit controller.RecordsChanged();

        return true;
    };

    //
    // Callback to save file contents and to select file name:

    TypeUiEditor::TypeSaveCallback save_as_callback =
        [&controller, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;

        QString file_dialog_options =
            this->FileFormatTitle() +
            QCoreApplication::translate( "TypeTextFileRecord", " files " ) +
            this->FileExtension();

        //
        // Take file name from a file dialog:

        QString file_name_out =
            QFileDialog::getSaveFileName(
                &controller.MainWindow(),
                QCoreApplication::translate( "TypeTextFileRecord", "Load File" ),
                this->FileFullName(),
                file_dialog_options );

        if( file_name_out.isEmpty() )
        {
            qDebug() << "File selection cancelled";
            return false;
        }

        //
        // Check file is not open yet:

        QString new_id = controller.NewFileNameId( file_name_out );

        if( editor->Id() != new_id )
        {
            if( controller.MainWindow().EditorContainer().HasId( new_id ) )
            {
                if( !TypeController::AcceptMessage(
                            QCoreApplication::translate(
                                "TypeTextFileRecord", "File already open. Replace file?" ) ) )
                    return false;

                controller.MainWindow().EditorContainer().Close( new_id );
            }

            editor->SetId( new_id );
        }

        //
        // Save file:

        editor->SetName( file_name_out );
        controller.SaveTextFile( file_name_out, editor->Text() );

        return true;
    };

    //
    // Build text editor object:

    text_editor = new TypeUiTextEditor(
        id, this->FileFullName(), this->FileName(), 0,
        save_callback, save_as_callback, syntax_highlighter );

    //
    // Load text contents:

    text_editor->SetText( TypeController::LoadTextFile( this->FileFullName() ) );
    text_editor->SetHasChanged( false );

    return text_editor;
}

TypeTextFileRecordFactory::TypeTextFileRecordFactory()
{
    m_RecordClass = "TextFile";
}

TypeRecord* TypeTextFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeTextFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeTextFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeTextFileRecord( state, parent, root );
}



