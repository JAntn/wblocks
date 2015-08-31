#ifndef TypeSTATEREADERTABLE_H
#define TypeSTATEREADERTABLE_H

#include "FW/ST/state_reader.h"

class TypeStateReaderTable : public TypeStateReader
{
public:

    TypeStateReaderTable(QList<QStringList>& table, long flags = 0, TypeVariant* parent = 0 );
    void                Read( QStringList& row ) override;

    M_CONST_POINTER     ( Table, QList<QStringList> )
};

#endif // TypeSTATEREADERTABLE_H
