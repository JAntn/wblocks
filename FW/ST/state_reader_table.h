#ifndef C_STATEREADERTABLE_H
#define C_STATEREADERTABLE_H

#include "FW/ST/state_reader.h"

class C_StateReaderTable : public C_StateReader
{
public:

    C_StateReaderTable(QList<QStringList>& table, long flags = 0, C_Variant* parent = 0 );
    void                Read( QStringList& row ) override;

    M_CONST_POINTER     ( Table, QList<QStringList> )
};

#endif // C_STATEREADERTABLE_H
