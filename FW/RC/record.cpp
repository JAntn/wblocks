
#include "FW/RC/record.h"

#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#include "FW/UI/PR/ui_recordname_property.h"
#include "FW/UI/PR/ui_valueopen_property.h"
#include "FW/UI/PR/ui_label_property.h"
#include "FW/UI/PR/ui_combo_property.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ED/ui_text_editor.h"

#include "FW/BK/html_block_stream.h"
#include "FW/tools.h"

#include <QVBoxLayout>

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

TypeRecord::TypeRecord( QString id, QString name, QString value, TypeVariant* parent ) :
    TypeVariant( parent ),
    m_Id( id ),
    m_Name( name ),
    m_Class( "Record" ),
    m_Value( value )
{
    SetFlags( FLAG_ACTION_ALL | FLAG_ROLE_BODY );
}

TypeRecord::TypeRecord( TypeStateWriter& state, TypeVariant* parent ):
    TypeRecord( "", "", "", parent )
{
    SetState( state );
}

TypeRecord::~TypeRecord()
{
    // void
}

void TypeRecord::SetValue( const QString& value )
{
    m_Value = value;
}

const QString& TypeRecord::Value() const
{
    return m_Value;
}

QString& TypeRecord::Value()
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
    row.append( QString::number( this->Flags() ) );
    state.Read( row );

    return true;
}

bool TypeRecord::SetState( TypeStateWriter& state )
{
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

    return true;
}

const QVector<long> RoleFlagList
{
    FLAG_ROLE_BODY,
    FLAG_ROLE_HEAD,
    FLAG_ROLE_JAVASCRIPT,
    FLAG_ROLE_CSS,
    FLAG_ROLE_PHP,
    0
};

const QStringList RoleStringList
{
    "Body",
    "Head",
    "Java Script",
    "Css",
    "Php",
    "None"
};

const QVector<QString> HighlightStringList
{
    "HTML",
    "HTML",
    "JAVASCRIPT",
    "CSS",
    "PHP",
    "TEXT"
};


int RecordRoleFlagIndex( TypeRecord& record )
{
    int index = 0;

    for( long role_flag : RoleFlagList )
    {
        if( record.Flags() & role_flag )
            break;

        ++index;
    }

    return index;
}

QWidget* TypeRecord::PropertyWidget( TypeController& controller )
{

    //
    // Class name label widget:

    QWidget* class_widget;
    class_widget = new TypeUiLabelProperty( "Class", this->Class() );

    //
    // Record name input widget:

    QWidget* name_widget;
    name_widget = new TypeUiRecordNameProperty(
        "Name", this->Name(), [&controller, this]( TypeUiProperty & property_base )
    {
        TypeVariantPtr<TypeUiRecordNameProperty> property = &property_base;
        this->SetName( property->Value() );
        emit controller.RecordChanged( this );
        emit controller.RecordChanged(/*generic slot*/);
        return true;
    } );

    //
    // Value input widget:

    TypeUiProperty::TypeSaveCallback save_callback = [&controller, this]( TypeUiProperty & property_base )
    {
        TypeVariantPtr<TypeUiValueOpenProperty> property = &property_base;
        this->SetValue( property->Value() );
        emit controller.RecordChanged( this );
        emit controller.RecordChanged(/*generic slot*/);
        return true;
    };

    TypeUiValueOpenProperty::TypeOpenCallback open_callback = [&controller, this]( TypeUiProperty& )
    {
        controller.OpenRecordEditorWidget( *this );
    };

    QWidget* value_widget;
    value_widget = new TypeUiValueOpenProperty( "Value", this->Value(), save_callback, open_callback );

    //
    // Role input widget:

    QWidget* combo_widget;
    combo_widget = new TypeUiComboProperty(
        "Role", RecordRoleFlagIndex( *this ), RoleStringList,
        [&controller, this]( TypeUiProperty & property_base )
    {
        TypeVariantPtr<TypeUiComboProperty> property = &property_base;
        int index = property->Value();

        if( index != -1 )
        {
            long role_flag = RoleFlagList[ index ];
            this->SetFlags( ( ( this->Flags() & ( ~FLAG_ROLE_ALL ) ) | role_flag ) );
            emit controller.RecordChanged( this );
            emit controller.RecordChanged(/*generic slot*/);
        }

        return true;
    } );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( class_widget );
    layout->addWidget( name_widget );
    layout->addWidget( value_widget );
    layout->addWidget( combo_widget );

    QWidget* widget = new QWidget;
    widget->setLayout( layout );

    return widget;
}


TypeUiEditor* TypeRecord::EditorWidget( QString id, TypeController& controller )
{

    TypeUiEditor::TypeSaveCallback save_callback = [&controller, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        this->SetValue( editor->Text() );
        controller.SetActiveRecord( this );
        emit controller.RecordChanged( this );
        emit controller.RecordChanged(/*generic slot*/);
        return true;
    };

    TypeUiEditor::TypeUpdateCallback update_callback = [this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        QString changed_mark = "";

        if( editor->HasChanged() )
            changed_mark = "*";

        editor->SetName( this->FullName() );
        editor->SetTabName( this->Name() );
        editor->SetTitle( editor->Name() + changed_mark );

        if( editor->EditorContainer() != 0 )
        {
            editor->EditorContainer()->SetTabName( editor->Id(), editor->TabName() + changed_mark );
            editor->EditorContainer()->SetTabToolTip( editor->Id(), editor->Name() + changed_mark );
        }

        return true;
    };

    TypeUiSyntaxHighlighter* syntax_highlighter =
        controller.SyntaxHighlighterFactory().NewInstance( HighlightStringList[RecordRoleFlagIndex( *this )] );


    TypeUiTextEditor* text_editor = new TypeUiTextEditor(
        id,
        this->FullName(),
        this->Name(),
        0 /*parent widget*/,
        save_callback,
        &TypeUiEditor::empty_save_callback,
        update_callback,
        syntax_highlighter );

    QObject::connect( &controller, TypeController::RecordChanged, [this, text_editor]( TypeRecord * record )
    {
        if( record == 0 )
            return;

        if( record == this || record->Struct() != 0 )
            text_editor->OnActionUpdate();
    } );

    QObject::connect( &controller, TypeController::RecordRemoved, [this, text_editor]( TypeRecord * record )
    {
        if( record == 0 )
            return;

        if( record == this )
            delete text_editor;
    } );

    text_editor->SetText( this->Value() );
    text_editor->SetHasChanged( false );

    return text_editor;
}

TypeStruct* TypeRecord::Struct() const
{
    return 0;
}

TypeStruct* TypeRecord::ParentStruct() const
{
    return TypeVariantPtr<TypeStruct>( this->Parent() );
}

TypeRecord* TypeRecord::ParentRecord() const
{
    TypeStruct* parent_struct = this->ParentStruct();

    if( parent_struct != 0 )
        return parent_struct->ParentRecord();

    return 0;
}

void TypeRecord::Html( TypeHtmlBlockStream& block_stream, long role, TypeStruct& root  )
{
    if( role & this->Flags() )
        block_stream.Append( ParseText( this->Value(), *this, root ), this->Id() );
}

QString TypeRecord::ParseText( const QString& text, TypeRecord& record, TypeStruct& root )
{
    QStringList output;
    QRegExp regex( "\\[\\?[^\\]]*\\]" );

    int index = text.indexOf( regex ), prev;
    int length = regex.matchedLength();
    output << QStringRef( &text, 0, index ).toString();

    while( index >= 0 )
    {
        QString parser_block;
        QString property_block;
        QString record_block;
        QString record_prefix;
        TypeRecord* record_target;

        //
        // [%parser_block]

        parser_block = QStringRef( &text, index + 2, length - 2 - 1 ).toString();

        //
        // [%record_block:property_block]

        int index_b = parser_block.indexOf( QRegExp( "\\." ) );

        if( index_b != -1 )
        {
            record_block = QStringRef( &parser_block, 0, index_b ).toString().replace( " ", "" );

            if( record.ParentRecord() != 0 )
                record_prefix = record.ParentRecord()->FullName() + "_";

            record_block.replace( "*", record_prefix );
            record_target = root.FromName( record_block, true );

            property_block = QStringRef( &parser_block, index_b + 1, parser_block.length() - index_b - 1 ).toString();
        }
        else
        {
            record_target = &record;
            property_block = parser_block;
        }

        //
        // Run property command:

        QStringList token_list = property_block.split( " ", QString::SkipEmptyParts );

        if( record_target != 0 )
            output << record_target->Property( token_list );
        else
            qDebug() << "warning: record not found:" << parser_block;

        //
        // Append output text:

        prev = index + length;
        index = text.indexOf( regex, prev );
        output << QStringRef( &text, prev, index - prev ).toString();
        length = regex.matchedLength();
    }


    return output.join( "" );
}

QString TypeRecord::Property( const QStringList& token_list )
{
    if( token_list[0] == "Name" )
        return Name();

    if( token_list[0] == "FullName" )
        return FullName();

    if( token_list[0] == "Value" )
        return Value();

    if( token_list[0] == "Id" )
        return Id();

    if( token_list[0] == "Class" )
        return Class();

    return "";
}


QString TypeRecord::FullName()
{
    TypeRecord* parent_record = this->ParentRecord();

    if( parent_record != 0 )
        return parent_record->FullName() + "_" + this->Name();

    return this->Name();
}

TypeRecordFactory::TypeRecordFactory() :
    m_RecordClass( "Record" )
{
    // void
}

TypeRecord* TypeRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent )
{
    return new TypeRecord( TypeRecordFactory::GenerateId(), name, value, parent );
}

TypeRecord* TypeRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent )
{
    return new TypeRecord( state, parent );
}






