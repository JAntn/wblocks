#include "FW/RC/integer_record.h"
#include "FW/UI/ui_integer_editor.h"
#include "FW/UI/ui_main_window.h"
#include <FW/ST/state_writer.h>
#include <FW/ST/state_reader.h>
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

C_IntegerRecord::C_IntegerRecord( QString id, QString name, QString value, C_Variant* parent ):
    C_Record( id, name, value, parent )
{
    if( m_Value.isEmpty() )
        m_Value = "0";
}

C_IntegerRecord::C_IntegerRecord( C_StateWriter& state, C_Variant* parent ):
    C_Record( "", "", "", parent )
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

void C_IntegerRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( Class() );
    state.Read( row );
}

void C_IntegerRecord::SetState( C_StateWriter& state )
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

QString C_IntegerRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

C_Record* C_IntegerRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_IntegerRecord* record = new C_IntegerRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_IntegerRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent )
{
    C_IntegerRecord* record = new C_IntegerRecord( state, parent );
    return record;
}





