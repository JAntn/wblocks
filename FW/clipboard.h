#ifndef TypeCLIPBOARD_H
#define TypeCLIPBOARD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

#include <QString>

class TypeClipboard : public TypeVariant
{
public:

    explicit TypeClipboard( TypeVariant* parent = 0 );

    void                Clear();
    void                Paste( TypeRecordStruct& record_struct, int position );
    void                Cut( const QList<TypeRecord*>& records );
    void                Copy( const QList<TypeRecord*>& records );
    bool                Empty();

    M_CONST_VALUE       ( Data, QList<TypeRecord*> )
    M_CONST_VALUE       ( Flags, long )
};

#endif // TypeCLIPBOARD_H
