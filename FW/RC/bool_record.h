#ifndef TypeBOOL_RECORD_H
#define TypeBOOL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeBoolRecord : public TypeRecord
{
public:

    explicit TypeBoolRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeBoolRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeBoolRecord() override;

    QWidget*            PropertyWidget(TypeController& controller ) override;

private:

    friend class        TypeBoolRecordFactory;
};

class TypeBoolRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeBoolRecordFactory )

    TypeBoolRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeBOOL_RECORD_H
