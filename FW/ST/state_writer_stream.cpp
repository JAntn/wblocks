#include "FW/ST/state_writer_stream.h"
#include <QDataStream>

TypeStateWriterStream::TypeStateWriterStream( QDataStream& data_stream, long flags, TypeVariant* parent )
    : TypeStateWriter( flags, parent )

{
    m_DataStream = &data_stream;

    bool at_end;
    ( *m_DataStream ) >> at_end;

    if( at_end )
    {
        Stop();
        return;
    }

    ( *m_DataStream ) >> m_Data;
}

void TypeStateWriterStream::Next()
{
    if( AtEnd() )
        return;

    ++m_Count;

    bool at_end;
    ( *m_DataStream ) >> at_end;


    if( at_end )
    {
        Stop();
        return;
    }

    ( *m_DataStream ) >> m_Data;
}
