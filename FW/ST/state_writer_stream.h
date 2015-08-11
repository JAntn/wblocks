#ifndef C_STATEWRITERSTREAM_H
#define C_STATEWRITERSTREAM_H

#include "FW/ST/state_writer.h"

class C_StateWriterStream : public C_StateWriter
{
public:

    C_StateWriterStream( QDataStream& data_stream, long flags = 0, C_Variant* parent = 0 );

    void                Next() override;

    ATR_CONST_POINTER   ( DataStream, QDataStream )

};

#endif // C_STATEWRITERSTREAM_H
