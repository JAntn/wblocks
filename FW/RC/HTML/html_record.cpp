#include "FW/RC/HTML/html_record.h"
#include "FW/UI/PR/ui_html_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/UI/ui_record_value_editor.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QCoreApplication>

C_HtmlRecord::C_HtmlRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Html";
}

C_HtmlRecord::C_HtmlRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Html";
    SetState( state, root );
}

C_HtmlRecord::~C_HtmlRecord()
{
    //void
}

QStringList C_HtmlRecord::Html()
{
    return QStringList( Value() );
}

void C_HtmlRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiHtmlRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_HtmlRecord::OpenInEditor( C_Document& document )
{
    // DEFAULT OPEN OPERATION (WILL BE EXTENDED)

    auto& main_window = document.MainWindow();
    QString editor_id = "RECORD:TEXT:" + Id();
    QString editor_name = Name();

    if( main_window.TextEditorContainer().HasId( editor_id ) )
    {
        if( C_Document::AcceptMessage(
                    QCoreApplication::translate( "C_HtmlRecord", "Record already opened.\n\nLoad again?" ) ) )
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

C_HtmlRecordFactory::C_HtmlRecordFactory()
{
    m_RecordClass = "Html";
}

C_Record* C_HtmlRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_HtmlRecord* record = new C_HtmlRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_HtmlRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_HtmlRecord* record = new C_HtmlRecord( state, parent, root );
    return record;
}


