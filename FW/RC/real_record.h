#ifndef TypeREAL_RECORD_H
#define TypeREAL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeRealRecord : public TypeRecord
{
public:

    explicit TypeRealRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeRealRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
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

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeREAL_RECORD_H
