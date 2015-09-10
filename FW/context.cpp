#include "FW/context.h"

TypeContext::TypeContext( TypeStruct& records, TypeScene& scene, TypeStruct* root, TypeVariant* parent ):
    TypeVariant( parent )
{
    m_Struct = &records;
    m_Scene = &scene;
    m_Root = root;
}

TypeContext::~TypeContext()
{
    // void
}


