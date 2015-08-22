#ifndef C_CONFIG_H
#define C_CONFIG_H

#include "FW/variant.h"
#include "FW/macro.h"
#include "FW/document.h"

class C_Config : public C_Variant
{
public:

    explicit C_Config( QString config_path, C_Variant* parent = 0 );

    void                Load();
    void                Save();

    QString             ConfigFullFileName();
    QString             ProjectFullFileName();

    ATR_VALUE           ( ConfigPath,     QString )
    ATR_VALUE           ( ConfigFileName, QString )

    ATR_VALUE           ( ProjectPath,     QString )
    ATR_VALUE           ( ProjectFileName, QString )

};

#endif // C_CONFIG_H
