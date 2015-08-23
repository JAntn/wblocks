#include "FW/ST/state_reader_stream.h"
#include <QDataStream>

C_StateReaderStream::C_StateReaderStream(
    QDataStream& data_stream,
    long flags,
    C_Variant* parent ):
    C_StateReader( flags, parent )
{
    m_DataStream = &data_stream;
}

void C_StateReaderStream::Read( QStringList& data )
{
    if( AtEnd() )
        return;

    ( *m_DataStream ) << false;
    ( *m_DataStream ) << data;
    ++m_Count;
}

void C_StateReaderStream::Stop()
{
    if( AtEnd() )
        return;

    ( *m_DataStream ) << true;
    m_Flags |= FLAG_STATE_ATEND;
}
