#include "FW/RC/integer_record.h"
#include "FW/UI/PR/ui_integer_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include <FW/ST/state_writer.h>
#include <FW/ST/state_reader.h>
#include <FW/document.h>


C_IntegerRecord::C_IntegerRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Integer";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

C_IntegerRecord::C_IntegerRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Integer";
    SetState( state, root );
}

C_IntegerRecord::~C_IntegerRecord()
{
    //void
}


void C_IntegerRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiIntegerRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

C_IntegerRecordFactory::C_IntegerRecordFactory()
{
    m_RecordClass = "Integer";
}

C_Record* C_IntegerRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    return new C_IntegerRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
}

C_Record* C_IntegerRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    return new C_IntegerRecord( state, parent, root );
}





