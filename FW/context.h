#ifndef TypeCONTEXT_H
#define TypeCONTEXT_H

#include "FW/macro.h"
#include "FW/variant.h"

class TypeRecordStruct;
class TypeScene;

class TypeContext : public TypeVariant
{
public:

    TypeContext( TypeRecordStruct& records, TypeScene& scene, TypeRecordStruct* root = 0, TypeVariant* parent = 0 );
    ~TypeContext() override;

    M_POINTER           ( Records, TypeRecordStruct )
    M_POINTER           ( Scene,   TypeScene )
    M_POINTER           ( Root,    TypeRecordStruct )

};

#endif // TypeCONTEXT_H
