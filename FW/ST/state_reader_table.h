#ifndef C_STATEREADERTABLE_H
#define C_STATEREADERTABLE_H

#include "FW/ST/state_reader.h"

class C_StateReaderTable : public C_StateReader
{
public:

    C_StateReaderTable( list<QStringList>& table, long flags = 0, C_Variant* parent = 0 );

    void                Read( QStringList& row ) override;

    ATR_CONST_POINTER   ( Table, list<QStringList> )
};

#endif // C_STATEREADERTABLE_H
