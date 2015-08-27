#ifndef C_JS_INTEGER_RECORD_H
#define C_JS_INTEGER_RECORD_H

#include "FW/RC/integer_record.h"
#include "FW/macro.h"

class C_StateWriter;
class C_StateReader;

class C_JsIntegerRecord : public C_IntegerRecord
{
public:

    explicit C_JsIntegerRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_JsIntegerRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_JsIntegerRecord() override;

    QStringList         Script()    override;

private:

    friend class        C_UiIntegerRecordProperties;
    friend class        C_JsIntegerRecordFactory;
};

class C_JsIntegerRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS    ( C_JsIntegerRecordFactory )

    C_JsIntegerRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_JS_INTEGER_RECORD_H
