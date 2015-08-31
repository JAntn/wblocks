#ifndef TypeSCRIPT_FILE_RECORD_H
#define TypeSCRIPT_FILE_RECORD_H

#include "FW/RC/file_record.h"
#include "FW/macro.h"

class TypeRecordStruct;
class TypeUiEditor;
class TypeController;

class TypeStateWriter;
class TypeStateReader;

class TypeScriptFileRecord: public TypeFileRecord
{

public:

    explicit TypeScriptFileRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeScriptFileRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeScriptFileRecord() override;

    QStringList         Script() override;
    TypeUiEditor*         EditorWidget( QString id, TypeController& controller ) override;

private:

    friend class        TypeScriptFileRecordFactory;
};

class TypeScriptFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS   ( TypeScriptFileRecordFactory )

    TypeScriptFileRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeSCRIPT_RECORD_H
