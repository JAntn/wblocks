#ifndef TypeJS_STRING_RECORD_H
#define TypeJS_STRING_RECORD_H

#include "FW/macro.h"
#include "FW/RC/string_record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeJsStringRecord : public TypeStringRecord
{

public:

    explicit TypeJsStringRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeJsStringRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsStringRecord() override;

    QStringList         Script()  override;

private:

    friend class        TypeJsStringRecordFactory;
};

class TypeJsStringRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeJsStringRecordFactory )

    TypeJsStringRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;

};

#endif // TypeJS_STRING_RECORD_H
