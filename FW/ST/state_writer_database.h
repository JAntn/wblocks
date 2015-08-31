#ifndef TypeSTATEWRITERDATABASE_H
#define TypeSTATEWRITERDATABASE_H

#include <FW/ST/state_writer.h>
#include <FW/database.h>

class TypeStateWriterDatabase : public TypeStateWriter
{
public:

    TypeStateWriterDatabase( TypeDatabase& database, QString table_name, QString field_name,
                           long size, long flags = 0, TypeVariant* parent = 0 );
    void                Next() override;

    M_CONST_POINTER     ( Database, TypeDatabase )
    M_CONST_VALUE       ( TableName, QString )
    M_CONST_VALUE       ( FieldName, QString )
    M_CONST_VALUE       ( Size, long )

};

#endif // TypeSTATEWRITERDATABASE_H
