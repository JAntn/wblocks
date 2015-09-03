#ifndef JS_REFERENCERECORD_H
#define JS_REFERENCERECORD_H

#include "FW/macro.h"
#include "FW/RC/reference_record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsReferenceRecord : public TypeReferenceRecord
{

public:

    explicit TypeJsReferenceRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypeJsReferenceRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsReferenceRecord() override;

    void                Script(TypeBlockStream& block_stream) override;

private:

    friend class        TypeJsReferenceRecordFactory;
};

class TypeJsReferenceRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeJsReferenceRecordFactory )

    TypeJsReferenceRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // JS_REFERENCERECORD_H
