#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "FW/macro.h"
#include <QString>

class TypeRecord;
class TypeRecordStruct;

class TypeClipboard : public TypeVariant
{
public:

    explicit TypeClipboard( TypeVariant* Parent = 0 );

    void                Clear();
    void                Paste( TypeRecordStruct& record_struct, int position );
    void                Cut( const QList<TypeRecord*>& records );
    void                Copy( const QList<TypeRecord*>& records );
    bool                Empty();

    M_CONST_VALUE       ( Data, QList<TypeRecord*> )
    M_CONST_VALUE       ( Flags, long )
};

#endif // CLIPBOARD_H
