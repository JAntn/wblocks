#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "FW/tools.h"

class TypeRecord;
class TypeStruct;
class TypeController;

class TypeClipboard : public TypeVariant
{
public:

    explicit TypeClipboard( TypeController& controller, TypeVariant* Parent = 0 );

    void                Clear();
    void                Paste( TypeStruct& record_struct, int position );
    void                Cut( const QList<TypeRecord*>& records );
    void                Copy( const QList<TypeRecord*>& records );
    bool                Empty();

    M_REFERENCE         ( Controller, TypeController )
    M_VALUE_READONLY    ( Data, QList<TypeRecord*> )
    M_VALUE_READONLY    ( Flags, long )
};

#endif // CLIPBOARD_H
