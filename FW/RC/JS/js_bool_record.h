#ifndef C_JS_BOOL_RECORD_H
#define C_JS_BOOL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/bool_record.h"

class C_StateWriter;
class C_StateReader;

class C_JsBoolRecord : public C_BoolRecord
{
public:

    explicit C_JsBoolRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_JsBoolRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_JsBoolRecord() override;

    QStringList         Script()    override;

private:

    friend class        C_JsBoolRecordFactory;
};

class C_JsBoolRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_JsBoolRecordFactory )

    C_JsBoolRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance(C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_JS_BOOL_RECORD_H
