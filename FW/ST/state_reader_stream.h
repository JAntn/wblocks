#ifndef C_STATEREADERSTREAM_H
#define C_STATEREADERSTREAM_H

#include "FW/ST/state_reader.h"

class C_StateReaderStream : public C_StateReader
{
public:

    C_StateReaderStream( QDataStream& data_stream, long flags = 0, C_Variant* parent = 0 );
    void                Read( QStringList& row ) override;
    void                Stop() override;

    M_CONST_POINTER     ( DataStream, QDataStream )
};



#endif // C_STATEREADERSTREAM_H
