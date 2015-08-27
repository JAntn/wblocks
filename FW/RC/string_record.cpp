#include "FW/RC/string_record.h"
#include "FW/UI/PR/ui_string_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include <FW/document.h>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/record.h"

C_StringRecord::C_StringRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "String";
}

C_StringRecord::C_StringRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root  ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "String";
    SetState( state, root );
}

C_StringRecord::~C_StringRecord()
{
    //void
}

void C_StringRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiStringRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

C_StringRecordFactory::C_StringRecordFactory()
{
    m_RecordClass = "String";
}

C_Record* C_StringRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_StringRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_StringRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_StringRecord( state, parent, root );
}

