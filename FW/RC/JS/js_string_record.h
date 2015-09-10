#ifndef JSSTRINGRECORD_H
#define JSSTRINGRECORD_H

#include "FW/RC/string_record.h"

class TypeStateReader;
class TypeStateWriter;
class TypeHtmlBlockStream;

class TypeJsStringRecord : public TypeStringRecord
{

public:

    explicit TypeJsStringRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeJsStringRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeJsStringRecord() override;

    void                Script( TypeHtmlBlockStream& block_stream )  override;

private:

    friend class        TypeJsStringRecordFactory;
};

class TypeJsStringRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeJsStringRecordFactory )

    TypeJsStringRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;

};

#endif // JS_STRINGRECORD_H
