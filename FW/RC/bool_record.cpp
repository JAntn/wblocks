#include "FW/RC/bool_record.h"
#include "FW/UI/PR/ui_bool_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "ui_boolrecordproperties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

C_BoolRecord::C_BoolRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Bool";

    if( m_Value.isEmpty() )
        m_Value = "False";
}

C_BoolRecord::C_BoolRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Bool";

    SetState( state, root );
}

C_BoolRecord::~C_BoolRecord()
{
    // void
}


void C_BoolRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiBoolRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

C_BoolRecordFactory::C_BoolRecordFactory()
{
    m_RecordClass = "Bool";
}

C_Record* C_BoolRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    return new C_BoolRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_BoolRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    return new C_BoolRecord( state, parent, root );
}





