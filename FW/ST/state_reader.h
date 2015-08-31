#ifndef TypeSTATE_READER_H
#define TypeSTATE_READER_H

#include <QStringList>

#include "FW/macro.h"
#include "FW/variant.h"

class TypeStateReader : public TypeVariant
{
public:

    TypeStateReader( long flags = 0, TypeVariant* parent = 0 );
    ~TypeStateReader() override;

    virtual void        Stop();
    virtual void        Read( QStringList& data) = 0;
    virtual bool        AtEnd();

    M_CONST_VALUE       ( Flags,      long )
    M_CONST_VALUE       ( Count,      long )

};

#endif

#include "FW/ST/state_reader_database.h"
#include "FW/ST/state_reader_stream.h"
#include "FW/ST/state_reader_table.h"
