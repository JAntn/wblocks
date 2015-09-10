#ifndef REALRECORD_H
#define REALRECORD_H

#include "FW/RC/record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeRealRecord : public TypeRecord
{
public:

    explicit TypeRealRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeRealRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeRealRecord() override;

    QWidget*            PropertyWidget( TypeController& controller ) override;

private:

    friend class        TypeRealRecordFactory;
};

class TypeRealRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeRealRecordFactory )

    TypeRealRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // REALRECORD_H
