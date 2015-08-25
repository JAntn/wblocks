
#include "FW/RC/real_record.h"
#include "FW/UI/ui_real_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "ui_realrecordproperties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"

#define CLASS_NAME "Real"

C_RealRecord::C_RealRecord( QString id, QString name, QString value, C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    if( m_Value.isEmpty() )
        m_Value = "0";
}

C_RealRecord::C_RealRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    SetState( state, root );
}

C_RealRecord::~C_RealRecord()
{
    //void
}

QString C_RealRecord::Script()
{
    return  "\n" + FullName() + " = " + Value() + ";";
}

QString C_RealRecord::Class() const
{
    return CLASS_NAME;
}

void C_RealRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiRealRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_RealRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( Class() );
    state.Read( row );
}

void C_RealRecord::SetState( C_StateWriter& state, C_RecordStruct* )
{
    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
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

QString C_RealRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}



