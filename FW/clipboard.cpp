#include "FW/SC/scene.h"
#include "FW/SC/scene_item.h"
#include "FW/RC/record.h"
#include "FW/RC/record_struct.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/clipboard.h"
#include "FW/document.h"

TypeClipboard::TypeClipboard( TypeVariant* parent ):
    TypeVariant( parent )
{
    // void
}

void TypeClipboard::Clear()
{
    m_Data.clear();
    m_Flags = 0;
}

void TypeClipboard::Copy( const QList<TypeRecord*>& records )
{
    Clear();
    m_Data = records;
    m_Flags = FLAG_STATE_NEWID;
}

bool TypeClipboard::Empty()
{
    return m_Data.empty();
}

void TypeClipboard::Cut( const QList<TypeRecord*>& records )
{
    Clear();
    m_Data = records;
    m_Flags = 0;
}

void TypeClipboard::Paste( TypeRecordStruct& record_struct, int position )
{
    QList<QStringList> table;
    QList<TypeVariant*>::iterator iter;

    if ( position < 0 )
        iter = record_struct.end();
    else
    {
        iter = record_struct.begin();

        for( int count = 0; count < position; count++ )
            ++iter;
    }

    TypeStateReaderTable reader( table );

    for( TypeRecord* record : Data() )
        record->GetState( reader );

    TypeStateWriterTable writer( table, m_Flags );

    while( !writer.AtEnd() )
        record_struct.NewRecord( writer, iter );

    Clear();
}

