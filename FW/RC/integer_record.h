#ifndef C_INTEGER_RECORD_H
#define C_INTEGER_RECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class C_StateWriter;
class C_StateReader;

class C_IntegerRecord : public C_Record
{
public:

    explicit C_IntegerRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_IntegerRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_IntegerRecord() override;

    QWidget*            PropertyWidget( C_Controller& controller ) override;

private:

    friend class        C_IntegerRecordFactory;
};

class C_IntegerRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS   ( C_IntegerRecordFactory )

    C_IntegerRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_INTEGER_RECORD_H
