#ifndef ROOTSTRUCT_H
#define ROOTSTRUCT_H

#include "FW/RC/struct.h"

class TypeRootStruct : public TypeStruct
{
public:

    explicit TypeRootStruct( TypeVariant* parent = 0 );
    ~TypeRootStruct() override;

    TypeRecord*                        ParentRecord() override;
    TypeStruct*                        ParentStruct() override;
};


#endif // STRUCT_H
