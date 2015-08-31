#ifndef TypeCONFIG_H
#define TypeCONFIG_H

#include "FW/variant.h"
#include "FW/macro.h"
#include "FW/document.h"

class TypeConfig : public TypeVariant
{
public:

    explicit TypeConfig( QString config_path, TypeVariant* parent = 0 );

    void                Load();
    void                Save();

    QString             ConfigFileFullName();
    QString             ProjectFileFullName();

    M_VALUE             ( ConfigPath,      QString )
    M_VALUE             ( ConfigFileName,  QString )
    M_VALUE             ( ProjectPath,     QString )
    M_VALUE             ( ProjectFileName, QString )

};

#endif // TypeCONFIG_H
