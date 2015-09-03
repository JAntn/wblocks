#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H

#include "FW/variant.h"
#include "FW/macro.h"

class TypeBlockStream;
class TypeRecordStruct;

class TypeHtmlBuilder : public TypeVariant
{
public:

    explicit TypeHtmlBuilder( TypeVariant* Parent = 0 );
    ~TypeHtmlBuilder() override;

    void                      Build( TypeRecordStruct& root );
    QString                   Text();

    M_POINTER                ( BlockStream,  TypeBlockStream )
};

#endif // HTMLBUILDER_H
