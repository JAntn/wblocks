#ifndef TypeSTRING_RECORD_H
#define TypeSTRING_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeStringRecord : public TypeRecord
{
public:

    explicit TypeStringRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeStringRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeStringRecord() override;

    QWidget*            PropertyWidget(TypeController& controller ) override;

private:

    friend class        TypeStringRecordFactory;
};

class TypeStringRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeStringRecordFactory )

    TypeStringRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeSTRING_RECORD_H
