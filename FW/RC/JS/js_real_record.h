#ifndef C_JS_REAL_RECORD_H
#define C_JS_REAL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/real_record.h"

class C_StateWriter;
class C_StateReader;

class C_JsRealRecord : public C_RealRecord
{
public:

    explicit C_JsRealRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_JsRealRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_JsRealRecord() override;

    QStringList         Script() override;

private:

    friend class        C_JsRealRecordFactory;
};

class C_JsRealRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS( C_JsRealRecordFactory )

    C_JsRealRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_JS_REAL_RECORD_H
