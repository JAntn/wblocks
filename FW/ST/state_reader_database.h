#ifndef C_STATEREADERDATABASE_H
#define C_STATEREADERDATABASE_H

#include <FW/ST/state_reader.h>
#include <FW/database.h>

class C_StateReaderDatabase : public C_StateReader
{
public:

    C_StateReaderDatabase( C_Database& database, QString table_name, QString field_name,
                           long flags = 0, C_Variant* parent = 0 );

    void                Read( QStringList& data ) override;

    M_CONST_POINTER     ( Database, C_Database )
    M_CONST_VALUE       ( TableName, QString )
    M_CONST_VALUE       ( FieldName, QString )
};

#endif // C_STATEREADERDATABASE_H
