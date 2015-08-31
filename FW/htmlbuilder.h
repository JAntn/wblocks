#ifndef TypeHTMLBUILDER_H
#define TypeHTMLBUILDER_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QStringList>

class TypeRecordStruct;

class TypeHtmlBuilder : public TypeVariant
{
public:

    explicit TypeHtmlBuilder( TypeVariant* parent = 0 );
    ~TypeHtmlBuilder() override;

    void                      Build( TypeRecordStruct& root );

    M_VALUE                   ( Html,  QStringList )
};

#endif // TypeHTMLBUILDER_H
