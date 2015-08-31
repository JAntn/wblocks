#ifndef TypeJS_REAL_RECORD_H
#define TypeJS_REAL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/real_record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsRealRecord : public TypeRealRecord
{
public:

    explicit TypeJsRealRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeJsRealRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsRealRecord() override;

    QStringList         Script() override;

private:

    friend class        TypeJsRealRecordFactory;
};

class TypeJsRealRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeJsRealRecordFactory )

    TypeJsRealRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeJS_REAL_RECORD_H
