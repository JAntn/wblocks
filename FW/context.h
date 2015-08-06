#ifndef C_DOCUMENTCONTEXT_H
#define C_DOCUMENTCONTEXT_H

#include "FW/macro.h"
#include "FW/variant.h"

class C_RecordStruct;
class C_Scene;

class C_Context : public C_Variant
{
public:
                        C_Context(C_RecordStruct& records, C_Scene& scene, C_Variant* parent=0);

    C_POINTER           (Records, C_RecordStruct)
    C_POINTER           (Scene,   C_Scene)

};

#endif // C_DOCUMENTCONTEXT_H
