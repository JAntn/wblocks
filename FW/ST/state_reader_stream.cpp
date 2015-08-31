#include "FW/ST/state_reader_stream.h"
#include <QDataStream>

TypeStateReaderStream::TypeStateReaderStream(
    QDataStream& data_stream,
    long flags,
    TypeVariant* parent ):
    TypeStateReader( flags, parent )
{
    m_DataStream = &data_stream;
}

void TypeStateReaderStream::Read( QStringList& data )
{
    if( AtEnd() )
        return;

    ( *m_DataStream ) << false;
    ( *m_DataStream ) << data;
    ++m_Count;
}

void TypeStateReaderStream::Stop()
{
    if( AtEnd() )
        return;

    ( *m_DataStream ) << true;
    m_Flags |= FLAG_STATE_ATEND;
}
