#ifndef VARIANT_H
#define VARIANT_H

#include "FW/macro.h"
#include <QList>

class TypeVariantStruct;

// REGLAS GENERALES
// Los objetos son eliminados mediante delete.
// El destructor se encarga de eliminar los objetos hijos y desreferenciar el objeto padre
// No implementar funciones Remove..
// No usar templates, directamente convertir desde este generico con static_cast

class TypeVariant
{
public:

    TypeVariant( TypeVariant* Parent = 0 );
    virtual ~TypeVariant();

    void                               SetParent( TypeVariant* Parent = 0 );
    TypeVariant*                       Parent() const;

    M_VALUE                            ( Childreen, QList<TypeVariant*> )

private:

    TypeVariant*                       m_Parent;
    friend class                       TypeVariantStruct;
};


#endif // VARIANT_H

#include "FW/variant_struct.h"
