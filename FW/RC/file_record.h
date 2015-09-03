#ifndef FILERECORD_H
#define FILERECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeFileRecord : public TypeRecord
{

public:

    explicit TypeFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypeFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
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

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // FILERECORD_H
