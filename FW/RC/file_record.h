#ifndef TypeFILE_RECORD_H
#define TypeFILE_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeFileRecord : public TypeRecord
{

public:

    explicit TypeFileRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeFileRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeFileRecord() override;

    QWidget*            PropertyWidget( TypeController& controller ) override;

    QString             FilePath();
    QString             FileName();
    QString             FileFullName();

private:

    friend class        TypeFileRecordFactory;
};

class TypeFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeFileRecordFactory )

    TypeFileRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeFILE_RECORD_H
