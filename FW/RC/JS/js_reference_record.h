#ifndef TypeJS_REFERENCE_RECORD_H
#define TypeJS_REFERENCE_RECORD_H

#include "FW/macro.h"
#include "FW/RC/reference_record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsReferenceRecord : public TypeReferenceRecord
{

public:

    explicit TypeJsReferenceRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeJsReferenceRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsReferenceRecord() override;

    QStringList         Script() override;

private:

    friend class        TypeJsReferenceRecordFactory;
};

class TypeJsReferenceRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeJsReferenceRecordFactory )

    TypeJsReferenceRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeJS_REFERENCE_RECORD_H
