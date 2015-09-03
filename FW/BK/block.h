#ifndef BLOCK_H
#define BLOCK_H

#include "FW/variant.h"
#include "FW/macro.h"
#include "FW/controller.h"

class TypeBlock : public TypeVariant
{
public:

    TypeBlock( int position, QString text, QString record_id, TypeVariant* Parent = 0 );

    M_VALUE             ( Position, int )
    M_VALUE             ( Text,     QString )
    M_VALUE             ( RecordId, QString )
};

#endif // BLOCK_H
