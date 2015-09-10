
#include "FW/RC/root_struct.h"

TypeRootStruct::TypeRootStruct( TypeVariant* parent ):
    TypeStruct( parent )
{
    // void
}

TypeRootStruct::~TypeRootStruct()
{
    // void
}

TypeRecord* TypeRootStruct::ParentRecord()
{
    return 0;
}

TypeStruct* TypeRootStruct::ParentStruct()
{
    return 0;
}
