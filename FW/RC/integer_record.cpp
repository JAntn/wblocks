#include "FW/RC/integer_record.h"
#include "FW/UI/ui_integer_editor.h"
#include "FW/UI/ui_main_window.h"

#include <QString>

#include <FW/data_state.h>
#include <FW/document.h>

#define CLASS_NAME "Integer"

QString C_IntegerRecord::Script() const
{
    return FullName() + " = " + Value() + ";";
}

C_RecordStruct* C_IntegerRecord::Struct() const
{
    return 0;
}

C_IntegerRecord::C_IntegerRecord( QString id, QString name, QString value, C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    // void
}

C_IntegerRecord::C_IntegerRecord( C_DataState& state, C_Variant* parent )
    : C_Record( "", "", "", parent )
{
    SetState( state );
}

C_IntegerRecord::~C_IntegerRecord()
{
    //void
}

QString C_IntegerRecord::Class() const
{
    return CLASS_NAME;
}

void C_IntegerRecord::ShowEditor( C_Document& document )
{
    QWidget* dialog = new C_UiIntegerEditor( *this, document, &document.MainWindow() );
    dialog->show();
}

void C_IntegerRecord::GetState( C_DataState& state )
{
    QStringList row;

    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( Class() );

    state.Append( row );
}

void C_IntegerRecord::SetState( C_DataState& state )
{
    QStringList row;

    state.Read( row );

    m_Id    = row.at( 0 );
    m_Name  = row.at( 1 );
    m_Value = row.at( 2 );
}

QString C_IntegerRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

C_Record* C_IntegerRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_IntegerRecord* record = new C_IntegerRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_IntegerRecordFactory::CreateInstance( C_DataState& state, C_Variant* parent )
{
    C_IntegerRecord* record = new C_IntegerRecord( state, parent );
    return record;
}





