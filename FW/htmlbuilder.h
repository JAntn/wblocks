#ifndef C_HTMLBUILDER_H
#define C_HTMLBUILDER_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QStringList>

class C_RecordStruct;

class C_HtmlBuilder : public C_Variant
{
public:

    explicit C_HtmlBuilder( C_Variant* parent = 0 );
    ~C_HtmlBuilder() override;

    void                      Build( C_RecordStruct& root );

    M_VALUE                   ( Html,  QStringList )
};

#endif // C_HTMLBUILDER_H
