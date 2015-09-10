#ifndef STATEWRITERDATABASE_H
#define STATEWRITERDATABASE_H

#include "FW/ST/state_writer.h"
#include "FW/database.h"

class TypeStateWriterDatabase : public TypeStateWriter
{
public:

    TypeStateWriterDatabase( TypeDatabase& database, QString table_name, QString field_name,
                           long size, long flags = 0, TypeVariant* Parent = 0 );
    void                Next() override;

    M_REFERENCE_READONLY                      ( Database, TypeDatabase )
    M_VALUE_READONLY                        ( TableName, QString )
    M_VALUE_READONLY                        ( FieldName, QString )
    M_VALUE_READONLY                        ( Size, long )

};

#endif // STATEWRITERDATABASE_H
