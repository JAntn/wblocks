#include "FW/RC/reference_record.h"
#include "FW/UI/ui_reference_record_properties.h"
#include "FW/UI/ui_main_window.h"
#include "ui_referencerecordproperties.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"

#define CLASS_NAME "Reference"

C_ReferenceRecord::C_ReferenceRecord( QString id, QString name, QString value, C_Variant* parent , C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Root = root;
}

C_ReferenceRecord::C_ReferenceRecord( C_StateWriter& state, C_Variant* parent , C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Root = root;
    SetState( state, root );
}

C_ReferenceRecord::~C_ReferenceRecord()
{
    // void
}

QString C_ReferenceRecord::Class() const
{
    return CLASS_NAME;
}

void C_ReferenceRecord::EditProperties( C_Document& document )
{
    QWidget* dialog = new C_UiReferenceRecordProperties( *this, document, &document.MainWindow() );
    dialog->show();
}

QString C_ReferenceRecord::Value()
{
    if( m_Value.isEmpty() )
        return "";

    C_Record* record = Referencee();

    if( record != 0 )
        return record->FullName();

    qDebug() << "Warning - Reference invalid:"
             << FullName();

    return "";
}

void C_ReferenceRecord::SetValue( QString full_name )
{
    C_Record* record =  Root().FromFullName( full_name );

    if( record != 0 )
    {
        m_Value = record->Id();
        return;
    }

    m_Value = "";
}

QString C_ReferenceRecord::Script()
{
    C_Record* record = Referencee();

    if( record != 0 )
        return "\n" + FullName() + " = " + record->FullName() + ";";

    qDebug() << "Warning - Reference invalid:"
             << FullName();

    return "";
}

C_Record* C_ReferenceRecord::Referencee()
{
    return Root().FromId( m_Value, true );
}

void C_ReferenceRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( m_Id );
    row.append( m_Name );
    row.append( m_Value );
    row.append( Class() );
    state.Read( row );
}

void C_ReferenceRecord::SetState( C_StateWriter& state , C_RecordStruct* root )
{
    m_Root = root;

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
}

C_Record* C_ReferenceRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_ReferenceRecord* record = new C_ReferenceRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_ReferenceRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_ReferenceRecord* record = new C_ReferenceRecord( state, parent, root );
    return record;
}

QString C_ReferenceRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}
