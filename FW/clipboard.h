#ifndef C_CLIPBOARD_H
#define C_CLIPBOARD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

#include <QString>

class C_Clipboard : public C_Variant
{
public:

    explicit C_Clipboard( C_Variant* parent = 0 );

    void                Clear();
    void                Paste( C_RecordStruct& record_struct, int position );
    void                Cut( const QList<C_Record*>& records );
    void                Copy( const QList<C_Record*>& records );
    bool                Empty();

    ATR_CONST_VALUE     ( Data, QList<C_Record*> )
    ATR_CONST_VALUE     ( Flags, long )
};

#endif // C_CLIPBOARD_H
