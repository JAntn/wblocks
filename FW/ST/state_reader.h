#ifndef STATEREADER_H
#define STATEREADER_H

#include "FW/tools.h"
#include "FW/ST/state_flags.h"


class TypeStateReader : public TypeVariant
{
public:

    TypeStateReader( long flags = 0, TypeVariant* Parent = 0 );
    ~TypeStateReader() override;

    virtual void        Stop();
    virtual void        Read( QStringList& data) = 0;
    virtual bool        AtEnd();

    M_VALUE_READONLY    ( Flags,      long )
    M_VALUE_READONLY    ( Count,      long )

};

#endif

#include "FW/ST/state_reader_database.h"
#include "FW/ST/state_reader_stream.h"
#include "FW/ST/state_reader_table.h"
