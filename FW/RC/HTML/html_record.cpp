#include "FW/RC/HTML/html_record.h"
#include "FW/UI/PR/ui_html_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include <QCoreApplication>

C_HtmlRecord::C_HtmlRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_StringRecord( id, name, value, parent, root )
{
    m_Class = "Html";
}

C_HtmlRecord::C_HtmlRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_StringRecord( "", "", "", parent, root )
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


