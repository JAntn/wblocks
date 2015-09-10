#ifndef STATEREADERTABLE_H
#define STATEREADERTABLE_H

#include "FW/ST/state_reader.h"

class TypeStateReaderTable : public TypeStateReader
{
public:

    TypeStateReaderTable(QList<QStringList>& table, long flags = 0, TypeVariant* Parent = 0 );
    void                Read( QStringList& row ) override;

    M_REFERENCE_READONLY  ( Table, QList<QStringList> )
};

#endif // STATEREADERTABLE_H
