#ifndef JSBOOLRECORD_H
#define JSBOOLRECORD_H

#include "FW/RC/bool_record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeJsBoolRecord : public TypeBoolRecord
{
public:

    explicit TypeJsBoolRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeJsBoolRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeJsBoolRecord() override;

    void                Script(TypeHtmlBlockStream& block_stream)    override;

private:

    friend class        TypeJsBoolRecordFactory;
};

class TypeJsBoolRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS     ( TypeJsBoolRecordFactory )

    TypeJsBoolRecordFactory();

    TypeRecord*         NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*         NewInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // JSBOOLRECORD_H
