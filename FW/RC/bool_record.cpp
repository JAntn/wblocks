
#include "FW/RC/bool_record.h"

#include "FW/UI/ui_bool_editor.h"
#include "FW/UI/ui_main_window.h"

#include "ui_booleditor.h"

#include <FW/data_state.h>

#include <FW/document.h>

#define CLASS_NAME "Bool"

C_BoolRecord::C_BoolRecord( QString id, QString name, QString value, C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    // void
}

C_BoolRecord::C_BoolRecord(C_DataState& state, C_Variant* parent)
    : C_Record( "", "", "", parent )

{
    SetState(state);
}

C_BoolRecord::~C_BoolRecord()
{
    //void
}

QString C_BoolRecord::Script() const
{
    return  FullName() + " = " + Value() + ";";
}

C_RecordStruct* C_BoolRecord::Struct() const
{
    return 0;
}

QString C_BoolRecord::Name() const
{
    return m_Name;
}


QString C_BoolRecord::Id() const
{
    return m_Id;
}

QString C_BoolRecord::Class() const
{
    return CLASS_NAME;
}

void C_BoolRecord::ShowEditor( C_Document& document )
{
    QWidget* dialog = new C_UiBoolEditor( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_BoolRecord::GetState( C_DataState& state )
{
    QStringList row;
    row.append( Id() );
    row.append( Name() );
    row.append( Value() );
    row.append( Class() );
    state.Append( row );
}

void C_BoolRecord::SetState( C_DataState& state )
{
    QStringList row;
    state.Read( row );
    m_Id    = row.at( 0 );
    m_Name  = row.at( 1 );
    m_Value = row.at( 2 );
}


C_Record* C_BoolRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_BoolRecord* record = new C_BoolRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_BoolRecordFactory::CreateInstance( C_DataState& state, C_Variant* parent )
{
    C_BoolRecord* record = new C_BoolRecord( state, parent );
    return record;
}

QString C_BoolRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}



