#ifndef BLOCKSTREAM_H
#define BLOCKSTREAM_H

#include "FW/variant.h"
#include "FW/variant.h"
#include "FW/macro.h"


class TypeBlockStream: protected TypeVariantStruct
{
public:

    using TypeVariantStruct::Size;
    using TypeVariantStruct::Clear;
    using TypeVariantStruct::begin;
    using TypeVariantStruct::end;

    TypeBlockStream( TypeVariant* Parent = 0 );

    void                Append( QString text, QString record_id = "" );

    M_VALUE             ( Count, int )
};

#endif // BLOCKSTREAM_H
