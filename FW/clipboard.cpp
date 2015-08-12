#include "clipboard.h"
#include "document.h"
#include "FW/SC/scene.h"
#include "FW/SC/scene_item.h"
#include "FW/RC/record_struct.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

C_Clipboard::C_Clipboard( C_Variant* parent ):
    C_Variant( parent )
{
    // void
}

void C_Clipboard::Clear()
{
    m_CopyList.clear();
    m_PasteFlags = 0;
}

void C_Clipboard::Copy( list<C_Record*>& records )
{
    Clear();
    m_CopyList = records;
    m_PasteFlags = FLAG_STATE_NEWID;
}

void C_Clipboard::Cut( list<C_Record*>& records )
{
    Clear();
    m_CopyList = records;
    m_PasteFlags = 0;
}

void C_Clipboard::Paste( C_RecordStruct& record_struct, int position )
{
    list<QStringList> table;
    C_RecordStruct::const_iterator iter;

    if ( position < 0 )
        iter = record_struct.end();
    else
    {
        iter = record_struct.begin();

        for( int count = 0; count < position; count++ )
            ++iter;
    }

    C_StateReaderTable reader( table );

    for( auto record : CopyList() )
        record->GetState( reader );

    C_StateWriterTable writer( table, m_PasteFlags );

    while( !writer.AtEnd() )
        record_struct.CreateRecord( writer, iter );

    Clear();
}

