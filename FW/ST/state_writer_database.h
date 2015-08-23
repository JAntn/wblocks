#ifndef C_STATEWRITERDATABASE_H
#define C_STATEWRITERDATABASE_H

#include <FW/ST/state_writer.h>
#include <FW/database.h>

class C_StateWriterDatabase : public C_StateWriter
{
public:

    C_StateWriterDatabase( C_Database& database,
        QString table_name, QString field_name, long size, long flags = 0, C_Variant* parent = 0 );

    void                Next() override;

    M_CONST_POINTER     ( Database, C_Database )
    M_CONST_VALUE       ( TableName, QString )
    M_CONST_VALUE       ( FieldName, QString )
    M_CONST_VALUE       ( Size, long )

};

#endif // C_STATEWRITERDATABASE_H
