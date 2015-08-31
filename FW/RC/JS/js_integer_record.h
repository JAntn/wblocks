#ifndef TypeJS_INTEGER_RECORD_H
#define TypeJS_INTEGER_RECORD_H

#include "FW/RC/integer_record.h"
#include "FW/macro.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsIntegerRecord : public TypeIntegerRecord
{
public:

    explicit TypeJsIntegerRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeJsIntegerRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsIntegerRecord() override;

    QStringList         Script()    override;

private:

    friend class        TypeJsIntegerRecordFactory;
};

class TypeJsIntegerRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS    ( TypeJsIntegerRecordFactory )

    TypeJsIntegerRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeJS_INTEGER_RECORD_H
