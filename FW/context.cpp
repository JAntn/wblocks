#include "FW/context.h"

C_Context::C_Context( C_RecordStruct& records, C_Scene& scene, C_RecordStruct* root, C_Variant* parent ):
    C_Variant( parent )
{
    m_Records = &records;
    m_Scene = &scene;
    m_Root = root;
}

C_Context::~C_Context()
{
    // void
}


