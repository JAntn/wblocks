#ifndef CONFIG_H
#define CONFIG_H

#include "FW/tools.h"

class TypeConfig : public TypeVariant
{
public:

    explicit TypeConfig( QString config_path, TypeVariant* Parent = 0 );

    void                Load();
    void                Save();

    M_VALUE             ( ConfigPath,      QString )
    M_VALUE             ( ConfigFileName,  QString )
    M_VALUE             ( ProjectPath,     QString )
    M_VALUE             ( ProjectFileName, QString )

};

#endif // CONFIG_H
