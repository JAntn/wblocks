#ifndef TypeHTML_RECORD_H
#define TypeHTML_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"
#include "FW/RC/string_record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeHtmlRecord : public TypeStringRecord
{

public:

    explicit TypeHtmlRecord( TypeStateWriter& state, TypeVariant* parent, TypeRecordStruct* root = 0 );
    TypeHtmlRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeHtmlRecord() override;

    QStringList         Html()  override;

private:

    friend class        TypeUiScriptRecordProperties;
    friend class        TypeHtmlRecordFactory;
};

class TypeHtmlRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeHtmlRecordFactory )

    TypeHtmlRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};


#endif // TypeHTML_RECORD_H
