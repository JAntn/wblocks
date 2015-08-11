#ifndef C_CLIPBOARD_H
#define C_CLIPBOARD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

#include <QString>

class C_Clipboard : public C_Variant
{
public:

    explicit C_Clipboard(C_Variant* parent=0);

    void                Clear();
    void                Copy(C_RecordStruct& from, QStringList& id_list);
    void                Paste(C_RecordStruct& into, int position);


    ATR_POINTER         (Records, C_RecordStruct)
    ATR_VALUE           (IdList,  QStringList)
};

#endif // C_CLIPBOARD_H
