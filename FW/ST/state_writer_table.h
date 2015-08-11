#ifndef C_STATEWRITERTABLE_H
#define C_STATEWRITERTABLE_H

#include "FW/ST/state_writer.h"

class C_StateWriterTable : public C_StateWriter
{
public:

    C_StateWriterTable( list<QStringList>& table, long flags = 0, C_Variant* parent = 0 );

    void                Next() override;

    ATR_CONST_POINTER   ( Table, list<QStringList> )
    ATR_CONST_VALUE     ( Iter,  list<QStringList>::iterator )

};

#endif // C_STATEWRITERTABLE_H
