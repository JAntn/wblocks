#ifndef PHPFILERECORD_H
#define PHPFILERECORD_H

#include "FW/RC/file_record.h"
#include "FW/macro.h"

class TypeRecordStruct;
class TypeUiEditor;
class TypeController;

class TypeStateWriter;
class TypeStateReader;

class TypePhpFileRecord: public TypeFileRecord
{

public:

    explicit TypePhpFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypePhpFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypePhpFileRecord() override;

    TypeUiEditor*       EditorWidget( QString id, TypeController& controller ) override;


private:

    friend class        TypePhpFileRecordFactory;
};

class TypePhpFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS   ( TypePhpFileRecordFactory )

    TypePhpFileRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // PHPFILERECORD_H
