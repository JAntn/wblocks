#ifndef C_TREE_NODE_H
#define C_TREE_NODE_H

#include "FW/macro.h"
#include <QString>

class C_VariantStruct;

// REGLAS GENERALES
// Los objetos son eliminados mediante delete.
// El destructor se encarga de eliminar los objetos hijos y desreferenciar el objeto padre
// No implementar funciones Remove..
// No usar templates, directamente convertir desde este generico con static_cast

class C_Variant
{
public:

    C_Variant(C_Variant* parent=0);
    virtual ~C_Variant();

    C_VALUE                            (Childreen, list<C_Variant*>)

    void                               SetParent(C_Variant* parent=0);
    C_Variant*                         Parent() const;

private:

    C_Variant*                         m_Parent;
    friend class                       C_VariantStruct;
};

#endif // C_TREE_NODE_H

#include "FW/variant_struct.h"
