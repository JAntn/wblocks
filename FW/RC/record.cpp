#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/UI/ui_record_value_editor.h"
#include "FW/UI/ui_record_properties.h"

long C_RecordFactory::m_IdCount = 0;

QString C_RecordFactory::GenerateId()
{
    return QString::number( m_IdCount++ );
}

QString C_RecordFactory::IdCount()
{
    return QString::number( m_IdCount );
}

C_Record::C_Record( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* ) :
    C_Variant( parent ),
    m_Id( id ),
    m_Name( name ),
    m_Value( value )
{
    SetFlags( FLAG_ACTION_ALL );
}

C_Record::~C_Record()
{
    // void
}

void C_Record::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_Record::OpenInEditor( C_Document& document )
{
    // DEFAULT OPEN OPERATION

    auto& main_window = document.MainWindow();
    QString editor_id = "RECORD:TEXT:" + Id();
    QString editor_name = Name();

    if( main_window.TextEditorContainer().HasId( editor_id ) )
    {
        if( C_Document::AcceptMessage( "Record already opened.\n\nLoad again?" ) )
        {
            main_window.TextEditorContainer().Close( editor_id );
            main_window.TextEditorContainer().Append( new C_UiRecordValueEditor( editor_id, editor_name, *this ) );
            emit document.Events().TextEditorContainerChanged();
            main_window.SetCurrentTab( MAINWINDOW_TAB_EDITOR );
        }

        return;
    }

    main_window.TextEditorContainer().Append( new C_UiRecordValueEditor( editor_id, editor_name, *this ) );
    emit document.Events().TextEditorContainerChanged();
    main_window.SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

C_RecordStruct* C_Record::Struct()
{
    return 0;
}

QString C_Record::Script()
{
    return "";
}

QString C_Record::Html()
{
    return "";
}

QString C_Record::FullName() const
{
    auto record_struct = static_cast<C_RecordStruct*>( Parent() );

    if( record_struct->Name() != "root" )
    {
        C_Record* record = static_cast<C_Record*>( record_struct->Parent() );
        return record->FullName() + "." + Name();
    }

    return Name();
}

void C_Record::SetValue( QString value )
{
    m_Value = value;
}

QString C_Record::Value()
{
    return m_Value;
}





