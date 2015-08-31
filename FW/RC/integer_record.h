#ifndef TypeINTEGER_RECORD_H
#define TypeINTEGER_RECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class TypeStateWriter;
class TypeStateReader;

class TypeIntegerRecord : public TypeRecord
{
public:

    explicit TypeIntegerRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeIntegerRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
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

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeINTEGER_RECORD_H
