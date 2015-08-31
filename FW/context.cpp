#include "FW/context.h"

TypeContext::TypeContext( TypeRecordStruct& records, TypeScene& scene, TypeRecordStruct* root, TypeVariant* parent ):
    TypeVariant( parent )
{
    m_Records = &records;
    m_Scene = &scene;
    m_Root = root;
}

TypeContext::~TypeContext()
{
    // void
}


