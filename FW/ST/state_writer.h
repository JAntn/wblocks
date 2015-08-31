#ifndef TypeSTATEWRITER_H
#define TypeSTATEWRITER_H

#include <QStringList>

#include "FW/macro.h"
#include "FW/variant.h"

class TypeStateWriter : public TypeVariant
{
public:

    TypeStateWriter( long flags = 0, TypeVariant* parent = 0 );
    ~TypeStateWriter();

    virtual void        Stop();
    virtual void        Write( QStringList& data, bool next = true);
    virtual bool        AtEnd();
    virtual void        Next() = 0;

    M_CONST_VALUE       ( Data,       QStringList )
    M_CONST_VALUE       ( Flags,      long )
    M_CONST_VALUE       ( Count,      long )

};

#endif // TypeSTATEWRITER_H

#include "FW/ST/state_writer_database.h"
#include "FW/ST/state_writer_stream.h"
#include "FW/ST/state_writer_table.h"
