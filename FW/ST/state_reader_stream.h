#ifndef TypeSTATEREADERSTREAM_H
#define TypeSTATEREADERSTREAM_H

#include "FW/ST/state_reader.h"

class TypeStateReaderStream : public TypeStateReader
{
public:

    TypeStateReaderStream( QDataStream& data_stream, long flags = 0, TypeVariant* parent = 0 );
    void                Read( QStringList& row ) override;
    void                Stop() override;

    M_CONST_POINTER     ( DataStream, QDataStream )
};



#endif // TypeSTATEREADERSTREAM_H
