#ifndef TypeSTATEREADERDATABASE_H
#define TypeSTATEREADERDATABASE_H

#include <FW/ST/state_reader.h>
#include <FW/database.h>

class TypeStateReaderDatabase : public TypeStateReader
{
public:

    TypeStateReaderDatabase( TypeDatabase& database, QString table_name, QString field_name,
                           long flags = 0, TypeVariant* parent = 0 );

    void                Read( QStringList& data ) override;

    M_CONST_POINTER     ( Database, TypeDatabase )
    M_CONST_VALUE       ( TableName, QString )
    M_CONST_VALUE       ( FieldName, QString )
};

#endif // TypeSTATEREADERDATABASE_H
