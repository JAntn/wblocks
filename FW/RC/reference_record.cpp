#include "FW/RC/reference_record.h"
#include "FW/UI/ui_reference_editor.h"
#include "FW/UI/ui_main_window.h"
#include "ui_referenceeditor.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/document.h"

#define CLASS_NAME "Reference"

C_ReferenceRecord::C_ReferenceRecord( QString id, QString name, QString value, C_Variant* parent )
    : C_Record( id, name, value, parent )
{
    m_Document = 0;
}

C_ReferenceRecord::C_ReferenceRecord( C_StateWriter& state, C_Variant* parent )
    : C_Record( "", "", "", parent )
{
    SetState( state );
}

C_ReferenceRecord::~C_ReferenceRecord()
{
    // void
}

QString C_ReferenceRecord::Script() const
{
    return  "";
}

C_RecordStruct* C_ReferenceRecord::Struct() const
{
    return 0;
}

QString C_ReferenceRecord::Class() const
{
    return CLASS_NAME;
}

void C_ReferenceRecord::ShowEditor( C_Document& document )
{
    QWidget* dialog = new C_UiReferenceEditor( *this, document, &document.MainWindow() );
    dialog->show();
}

QString C_ReferenceRecord::Value() const
{
    if( m_Value.isEmpty() )
        return "";

    auto record = Document()
                  .Records()
                  .FromId( m_Value, true );

    if( record == 0 )
        return "";

    return record->FullName();
}

void C_ReferenceRecord::SetValue( QString full_name )
{
    QStringList string_list = full_name.split( "." );
    C_Record* record;
    C_RecordStruct* record_struct = &Document().Records();

    for( auto
            iter = string_list.begin();
            iter != string_list.end();
            ++iter )
    {
        auto str = *iter;
        record = record_struct->FromName( str );

        if( record == 0 )
            break;
        else
        {
            auto tmp = iter;

            if( ( ++tmp ) == string_list.end() )
            {
                m_Value = record->Id();
                return;
            }
            else
            {
                if( record->Struct() != 0 )
                    record_struct = record->Struct();
                else
                    break;
            }
        }
    }

    m_Value = "";
}

C_Record* C_ReferenceRecord::Referencee()
{
    return Document()
                  .Records()
                  .FromId( m_Value, true );
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

void C_ReferenceRecord::SetState( C_StateWriter& state )
{
    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row.at( 0 );

    m_Name  = row.at( 1 );
    m_Value = row.at( 2 );
}

C_Record* C_ReferenceRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent )
{
    C_ReferenceRecord* record = new C_ReferenceRecord( C_RecordFactory::GenerateId(), name, value, parent );
    return record;
}

C_Record* C_ReferenceRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent )
{
    C_ReferenceRecord* record = new C_ReferenceRecord( state, parent );
    return record;
}

QString C_ReferenceRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}
