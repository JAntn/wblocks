#include "clipboard.h"
#include "FW/RC/record_struct.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

C_Clipboard::C_Clipboard( C_Variant* parent ):
    C_Variant( parent ), m_Records( 0 )
{
    // void
}

void C_Clipboard::Clear()
{
    m_Records = 0;
    m_IdList.clear();
}

void C_Clipboard::Copy( C_RecordStruct& record_struct, QStringList& id_list )
{
    Clear();
    m_Records = &record_struct;
    m_IdList = id_list;
}

void C_Clipboard::Paste( C_RecordStruct& record_struct, int position )
{
    list<QStringList> table;
    C_StateReaderTable reader( table );

    for( QString id : IdList() )
    {
        auto record = Records().FromId( id, true );

        if( record == 0 )
            return;

        record->GetState( reader );
    }

    C_RecordStruct::const_iterator iter;

    if ( position < 0 )
        iter = record_struct.end();
    else
    {
        iter = record_struct.begin();

        for( int count = 0; count < position; count++ )
            ++iter;
    }

    C_StateWriterTable writer( table, FLAG_STATE_NEWID);

    while( !writer.AtEnd() )
        record_struct.CreateRecord( writer, iter );

    Clear();
}

