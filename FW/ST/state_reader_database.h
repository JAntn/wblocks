#ifndef STATEREADERDATABASE_H
#define STATEREADERDATABASE_H

#include "FW/ST/state_reader.h"
#include "FW/database.h"

class TypeStateReaderDatabase : public TypeStateReader
{
public:

    TypeStateReaderDatabase( TypeDatabase& database, QString table_name, QString field_name,
                           long flags = 0, TypeVariant* Parent = 0 );

    void                Read( QStringList& data ) override;

    M_REFERENCE_READONLY  ( Database, TypeDatabase )
    M_VALUE_READONLY    ( TableName, QString )
    M_VALUE_READONLY    ( FieldName, QString )
};

#endif // STATEREADERDATABASE_H
