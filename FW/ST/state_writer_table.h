#ifndef TypeSTATEWRITERTABLE_H
#define TypeSTATEWRITERTABLE_H

#include "FW/ST/state_writer.h"

class TypeStateWriterTable : public TypeStateWriter
{
public:

    TypeStateWriterTable(QList<QStringList>& table, long flags = 0, TypeVariant* parent = 0 );
    void                Next() override;

    M_CONST_POINTER     ( Table, QList<QStringList> )
    M_CONST_VALUE       ( Iter,  QList<QStringList>::iterator )

};

#endif // TypeSTATEWRITERTABLE_H
