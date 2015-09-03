#ifndef STATEWRITERSTREAM_H
#define STATEWRITERSTREAM_H

#include "FW/ST/state_writer.h"

class TypeStateWriterStream : public TypeStateWriter
{
public:

    TypeStateWriterStream( QDataStream& data_stream, long flags = 0, TypeVariant* Parent = 0 );
    void                Next() override;

    M_CONST_POINTER     ( DataStream, QDataStream )

};

#endif // STATEWRITERSTREAM_H
