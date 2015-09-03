#ifndef INTEGERRECORD_H
#define INTEGERRECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class TypeStateWriter;
class TypeStateReader;

class TypeIntegerRecord : public TypeRecord
{
public:

    explicit TypeIntegerRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypeIntegerRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypeIntegerRecord() override;

    QWidget*            PropertyWidget( TypeController& controller ) override;

private:

    friend class        TypeIntegerRecordFactory;
};

class TypeIntegerRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS   ( TypeIntegerRecordFactory )

    TypeIntegerRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // INTEGERRECORD_H
