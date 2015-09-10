#ifndef STATEWRITERTABLE_H
#define STATEWRITERTABLE_H

#include "FW/ST/state_writer.h"

class TypeStateWriterTable : public TypeStateWriter
{
public:

    TypeStateWriterTable(QList<QStringList>& table, long flags = 0, TypeVariant* Parent = 0 );
    void                Next() override;

    M_REFERENCE_READONLY  ( Table, QList<QStringList> )
    M_VALUE_READONLY    ( Iter,  QList<QStringList>::iterator )

};

#endif // STATEWRITERTABLE_H
