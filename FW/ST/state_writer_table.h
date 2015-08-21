#ifndef C_STATEWRITERTABLE_H
#define C_STATEWRITERTABLE_H

#include "FW/ST/state_writer.h"

class C_StateWriterTable : public C_StateWriter
{
public:

    C_StateWriterTable(QList<QStringList>& table, long flags = 0, C_Variant* parent = 0 );

    void                Next() override;

    ATR_CONST_POINTER   ( Table, QList<QStringList> )
    ATR_CONST_VALUE     ( Iter,  QList<QStringList>::iterator )

};

#endif // C_STATEWRITERTABLE_H
