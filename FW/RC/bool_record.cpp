#include "FW/RC/bool_record.h"
#include "FW/UI/ui_bool_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "ui_boolrecordproperties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#define CLASS_NAME "Bool"

C_BoolRecord::C_BoolRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    if( m_Value.isEmpty() )
        m_Value = "False";
}

C_BoolRecord::C_BoolRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    SetState( state, root );
}

C_BoolRecord::~C_BoolRecord()
{
    //void
}

QString C_BoolRecord::Script()
{
    return  "\n" + FullName() + " = " + Value() + ";";
}

QString C_BoolRecord::Class() const
{
    return CLASS_NAME;
}

void C_BoolRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiBoolRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_BoolRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( Id() );
    row.append( Name() );
    row.append( Value() );
    row.append( Class() );
    state.Read( row );
}

void C_BoolRecord::SetState( C_StateWriter& state , C_RecordStruct* )
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

C_Record* C_BoolRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_BoolRecord* record = new C_BoolRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_BoolRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_BoolRecord* record = new C_BoolRecord( state, parent, root );
    return record;
}

QString C_BoolRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}



