#ifndef TypeSCRIPT_RECORD_H
#define TypeSCRIPT_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeScriptRecord : public TypeRecord
{

public:

    explicit TypeScriptRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root = 0 );
    TypeScriptRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeScriptRecord() override;

    QStringList         Script()  override;
    QWidget*            PropertyWidget( TypeController& controller ) override;
    TypeUiEditor*         EditorWidget( QString id, TypeController& document ) override;

private:

    friend class        TypeScriptRecordFactory;
};

class TypeScriptRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeScriptRecordFactory )

    TypeScriptRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // TypeSCRIPT_RECORD_H
