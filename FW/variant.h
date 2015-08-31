#ifndef TypeVARIANT_H
#define TypeVARIANT_H

#include "FW/macro.h"
#include <QString>

class TypeVariantStruct;

// REGLAS GENERALES
// Los objetos son eliminados mediante delete.
// El destructor se encarga de eliminar los objetos hijos y desreferenciar el objeto padre
// No implementar funciones Remove..
// No usar templates, directamente convertir desde este generico con static_cast

class TypeVariant
{
public:

    TypeVariant( TypeVariant* parent = 0 );
    virtual ~TypeVariant();

    void                               SetParent( TypeVariant* parent = 0 );
    TypeVariant*                         Parent() const;

    M_VALUE                            ( Childreen, QList<TypeVariant*> )

private:

    TypeVariant*                         m_Parent;
    friend class                       TypeVariantStruct;
};

#endif // TypeVARIANT_H

#include "FW/variant_struct.h"
