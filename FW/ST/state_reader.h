#ifndef C_STATE_READER_H
#define C_STATE_READER_H

#include <QStringList>

#include "FW/macro.h"
#include "FW/variant.h"

class C_StateReader : public C_Variant
{
public:

    C_StateReader( long flags = 0, C_Variant* parent = 0 );
    ~C_StateReader() override;

    virtual void        Stop();
    virtual void        Read( QStringList& data) = 0;
    virtual bool        AtEnd();

    ATR_CONST_VALUE     ( Flags,      long )

    // The number of records inserted to state
    ATR_CONST_VALUE     ( Count,      long )

};

#endif

#include "FW/ST/state_reader_database.h"
#include "FW/ST/state_reader_stream.h"
#include "FW/ST/state_reader_table.h"
