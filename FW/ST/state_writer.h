#ifndef C_STATEWRITER_H
#define C_STATEWRITER_H

#include <QStringList>

#include "FW/macro.h"
#include "FW/variant.h"

class C_StateWriter : public C_Variant
{
public:

    C_StateWriter( long flags = 0, C_Variant* parent = 0 );
    ~C_StateWriter();

    virtual void        Stop();
    virtual void        Write( QStringList& data, bool next = true);
    virtual bool        AtEnd();
    virtual void        Next() = 0;

    M_CONST_VALUE       ( Data,       QStringList )
    M_CONST_VALUE       ( Flags,      long )
    M_CONST_VALUE       ( Count,      long )

};

#endif // C_STATEWRITER_H

#include "FW/ST/state_writer_database.h"
#include "FW/ST/state_writer_stream.h"
#include "FW/ST/state_writer_table.h"
