#ifndef STATEWRITER_H
#define STATEWRITER_H

#include "FW/tools.h"
#include "FW/ST/state_flags.h"

class TypeStateWriter : public TypeVariant
{
public:

    TypeStateWriter( long flags = 0, TypeVariant* Parent = 0 );
    ~TypeStateWriter();

    virtual void        Stop();
    virtual void        Write( QStringList& data, bool next = true);
    virtual bool        AtEnd();
    virtual void        Next() = 0;

    M_VALUE_READONLY    ( Data,       QStringList )
    M_VALUE_READONLY    ( Flags,      long )
    M_VALUE_READONLY    ( Count,      long )

};

#endif // STATEWRITER_H

#include "FW/ST/state_writer_database.h"
#include "FW/ST/state_writer_stream.h"
#include "FW/ST/state_writer_table.h"
