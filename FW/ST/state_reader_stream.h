#ifndef STATEREADERSTREAM_H
#define STATEREADERSTREAM_H

#include "FW/ST/state_reader.h"

class TypeStateReaderStream : public TypeStateReader
{
public:

    TypeStateReaderStream( QDataStream& data_stream, long flags = 0, TypeVariant* Parent = 0 );
    void                Read( QStringList& row ) override;
    void                Stop() override;

    M_REFERENCE_READONLY  ( DataStream, QDataStream )
};



#endif // STATEREADERSTREAM_H
