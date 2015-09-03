#ifndef HTMLRECORD_H
#define HTMLRECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"
#include "FW/RC/string_record.h"

class TypeStateReader;
class TypeStateWriter;
class TypeBlockStream;

class TypeHtmlRecord : public TypeStringRecord
{

public:

    explicit TypeHtmlRecord( TypeStateWriter& state, TypeVariant* Parent, TypeRecordStruct* root = 0 );
    TypeHtmlRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypeHtmlRecord() override;

    void                Html( TypeBlockStream& block_stream )  override;

private:

    friend class        TypeHtmlRecordFactory;
};

class TypeHtmlRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeHtmlRecordFactory )

    TypeHtmlRecordFactory();

    TypeRecord*         NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*         NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};


#endif // HTMLRECORD_H
