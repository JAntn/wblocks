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
    m_Data.clear();
    m_Flags = 0;
}

void C_Clipboard::Copy( const QList<C_Record*>& records )
{
    Clear();
    m_Data = records;
    m_Flags = FLAG_STATE_NEWID;
}

bool C_Clipboard::Empty()
{
    return m_Data.empty();
}

void C_Clipboard::Cut( const QList<C_Record*>& records )
{
    Clear();
    m_Data = records;
    m_Flags = 0;
}

void C_Clipboard::Paste( C_RecordStruct& record_struct, int position )
{
    QList<QStringList> table;
    QList<C_Variant*>::iterator iter;

    if ( position < 0 )
        iter = record_struct.end();
    else
    {
        iter = record_struct.begin();

        for( int count = 0; count < position; count++ )
            ++iter;
    }

    C_StateReaderTable reader( table );

    for( auto record : Data() )
        record->GetState( reader );

    C_StateWriterTable writer( table, m_Flags );

    while( !writer.AtEnd() )
        record_struct.CreateRecord( writer, iter );

    Clear();
}

