#ifndef C_JS_STRING_RECORD_H
#define C_JS_STRING_RECORD_H

#include "FW/macro.h"
#include "FW/RC/string_record.h"

class C_StateReader;
class C_StateWriter;

class C_JsStringRecord : public C_StringRecord
{

public:

    explicit C_JsStringRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_JsStringRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_JsStringRecord() override;

    QStringList         Script()  override;

private:

    friend class        C_UiStringRecordProperties;
    friend class        C_JsStringRecordFactory;
};

class C_JsStringRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_JsStringRecordFactory )

    C_JsStringRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;

};

#endif // C_JS_STRING_RECORD_H
