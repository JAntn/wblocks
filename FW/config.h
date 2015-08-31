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

    QString             ConfigFileFullName();
    QString             ProjectFileFullName();

    M_VALUE             ( ConfigPath,      QString )
    M_VALUE             ( ConfigFileName,  QString )
    M_VALUE             ( ProjectPath,     QString )
    M_VALUE             ( ProjectFileName, QString )

};

#endif // C_CONFIG_H
