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

    explicit            C_Script(C_Document& document, C_Variant* parent=0);
    void                Generate(C_RecordStruct& record_container);

    C_POINTER           (Document,   C_Document)
    C_VALUE             (StringList, QStringList)
};

#endif // C_SCRIPT_H
