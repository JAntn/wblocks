#ifndef JS_INTEGERRECORD_H
#define JS_INTEGERRECORD_H

#include "FW/RC/integer_record.h"
#include "FW/macro.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsIntegerRecord : public TypeIntegerRecord
{
public:

    explicit TypeJsIntegerRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypeJsIntegerRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsIntegerRecord() override;

    void                Script( TypeBlockStream& block_stream )    override;

private:

    friend class        TypeJsIntegerRecordFactory;
};

class TypeJsIntegerRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS    ( TypeJsIntegerRecordFactory )

    TypeJsIntegerRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // JS_INTEGERRECORD_H
