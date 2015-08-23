#ifndef C_SCRIPT_H
#define C_SCRIPT_H

#include "FW/variant.h"
#include "FW/document.h"
#include "FW/macro.h"
#include <QStringList>

class C_RecordStruct;

class C_Script : public C_Variant
{
public:

    explicit C_Script( C_Variant* parent = 0 );
    ~C_Script() override;

    void                      Parse(C_RecordStruct& records );

    M_VALUE                   ( StringList, QStringList )
};

#endif // C_SCRIPT_H
