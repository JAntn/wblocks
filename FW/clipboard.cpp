#include "FW/SC/scene.h"
#include "FW/SC/scene_item.h"
#include "FW/RC/record.h"
#include "FW/RC/struct.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/clipboard.h"
#include "FW/document.h"
#include "FW/controller.h"

TypeClipboard::TypeClipboard( TypeController& controller, TypeVariant* parent ):
    TypeVariant( parent ),
    m_Controller( &controller )
{
    // void
}

void TypeClipboard::Clear()
{
    for( TypeRecord* record : Data() )
        Controller().RecordRemoved( record );

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

void TypeClipboard::Paste( TypeStruct& record_struct, int position )
{
    //
    // Make a deep copy of clipboard contents:

    QList<QStringList> table;
    TypeStateReaderTable reader( table );

    for( TypeRecord* record : Data() )
        record->GetState( reader );

    TypeStateWriterTable writer( table, m_Flags );

    while( !writer.AtEnd() )
        record_struct.NewRecord( writer, position );

    Clear();
}

