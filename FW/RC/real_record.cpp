
#include "FW/RC/real_record.h"
#include "FW/UI/PR/ui_real_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "ui_realrecordproperties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"


C_RealRecord::C_RealRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Class = "Real";

    if( m_Value.isEmpty() )
        m_Value = "0";
}

C_RealRecord::C_RealRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Class = "Real";
    SetState( state, root );
}

C_RealRecord::~C_RealRecord()
{
    //void
}

void C_RealRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiRealRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

C_RealRecordFactory::C_RealRecordFactory()
{
    m_RecordClass = "Real";
}

C_Record* C_RealRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent , C_RecordStruct* root )
{
    C_RealRecord* record = new C_RealRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_RealRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root )
{
    C_RealRecord* record = new C_RealRecord( state, parent, root );
    return record;
}




