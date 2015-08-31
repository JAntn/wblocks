#ifndef C_BOOL_RECORD_H
#define C_BOOL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_StateWriter;
class C_StateReader;

class C_BoolRecord : public C_Record
{
public:

    explicit C_BoolRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_BoolRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_BoolRecord() override;

    QWidget*            PropertyWidget(C_Controller& controller ) override;

private:

    friend class        C_BoolRecordFactory;
};

class C_BoolRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_BoolRecordFactory )

    C_BoolRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance(C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_BOOL_RECORD_H
