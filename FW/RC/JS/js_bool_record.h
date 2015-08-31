#ifndef TypeJS_BOOL_RECORD_H
#define TypeJS_BOOL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/bool_record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsBoolRecord : public TypeBoolRecord
{
public:

    explicit TypeJsBoolRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeJsBoolRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeJsBoolRecord() override;

    QStringList         Script()    override;

private:

    friend class        TypeJsBoolRecordFactory;
};

class TypeJsBoolRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeJsBoolRecordFactory )

    TypeJsBoolRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeJS_BOOL_RECORD_H
