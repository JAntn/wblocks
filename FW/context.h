#ifndef C_CONTEXT_H
#define C_CONTEXT_H

#include "FW/macro.h"
#include "FW/variant.h"

class C_RecordStruct;
class C_Scene;

class C_Context : public C_Variant
{
public:

    C_Context( C_RecordStruct& records, C_Scene& scene, C_RecordStruct* root = 0, C_Variant* parent = 0 );
    ~C_Context() override;

    M_POINTER           ( Records, C_RecordStruct )
    M_POINTER           ( Scene,   C_Scene )
    M_POINTER           ( Root,    C_RecordStruct )

};

#endif // C_CONTEXT_H
