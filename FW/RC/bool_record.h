#ifndef BOOLRECORD_H
#define BOOLRECORD_H

#include "FW/RC/record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeBoolRecord : public TypeRecord
{
public:

    explicit TypeBoolRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeBoolRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeBoolRecord() override;

    QWidget*            PropertyWidget( TypeController& controller ) override;

private:

    friend class        TypeBoolRecordFactory;
};

class TypeBoolRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeBoolRecordFactory )

    TypeBoolRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // BOOLRECORD_H
