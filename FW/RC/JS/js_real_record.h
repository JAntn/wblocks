#ifndef JSREALRECORD_H
#define JSREALRECORD_H

#include "FW/RC/real_record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsRealRecord : public TypeRealRecord
{
public:

    explicit TypeJsRealRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeJsRealRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeJsRealRecord() override;

    void                Script(TypeHtmlBlockStream& block_stream) override;

private:

    friend class        TypeJsRealRecordFactory;
};

class TypeJsRealRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeJsRealRecordFactory )

    TypeJsRealRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // JS_REALRECORD_H
