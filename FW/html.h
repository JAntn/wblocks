#ifndef C_HTML_H
#define C_HTML_H

#include "FW/variant.h"
#include "FW/document.h"
#include "FW/macro.h"
#include <QStringList>

class C_RecordStruct;

class C_Html : public C_Variant
{
public:

    explicit C_Html( C_Variant* parent = 0 );
    ~C_Html() override;

    void                      Parse(C_RecordStruct& root );

    M_VALUE                   ( StringList, QStringList )
};

#endif // C_HTML_H
