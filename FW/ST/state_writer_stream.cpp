#include "FW/ST/state_writer_stream.h"
#include <QDataStream>

C_StateWriterStream::C_StateWriterStream( QDataStream& data_stream, long flags, C_Variant* parent )
    : C_StateWriter( flags, parent )

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

void C_StateWriterStream::Next()
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
