#ifndef C_JS_REFERENCE_RECORD_H
#define C_JS_REFERENCE_RECORD_H

#include "FW/macro.h"
#include "FW/RC/reference_record.h"

class C_StateWriter;
class C_StateReader;

class C_JsReferenceRecord : public C_ReferenceRecord
{

public:

    explicit C_JsReferenceRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_JsReferenceRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_JsReferenceRecord() override;

    QStringList         Script() override;

private:

    friend class        C_JsReferenceRecordFactory;
};

class C_JsReferenceRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS( C_JsReferenceRecordFactory )

    C_JsReferenceRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_JS_REFERENCE_RECORD_H
