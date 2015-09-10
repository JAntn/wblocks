#ifndef VARIANTPTR_H
#define VARIANTPTR_H

#include "FW/variant.h"
#include <QDebug>

// TypeVariantPtr
// -----------------------------------------------------------------------------------
// Takes a pure TypeVariant pointer
// and generates 'pointer casts operations'
// towards specified derived type in
// template declaration
//
// example:  vector<TypeVariant*> v;
//           v.append(new TypeRealRecord)
//           v.append(new TypeIntegerRecord)
//            ...
//           if (v[i].Class() == "Integer")
//           {
//                 TypeVariantPtr<TypeIntegerRecord> integer_ptr = v[i]; // caution
//                 integer_val->SetValue("25");
//           }
// END --

template<class T>
class TypeVariantPtr
{
public:


    TypeVariantPtr( TypeVariant* variant )
    {
        m_Variant = variant;
    }

    TypeVariantPtr()
    {
        m_Variant = 0;
    }

    TypeVariantPtr( const TypeVariantPtr<T>& variant )
    {
        m_Variant = variant.m_Variant;
    }

    TypeVariantPtr<T>& operator=( TypeVariant* variant )
    {
        m_Variant = variant;
        return *this;
    }

    TypeVariantPtr<T>& operator=( const TypeVariantPtr<T>& variant )
    {

        m_Variant = variant.m_Variant;
        return *this;
    }

    T* operator->()
    {
#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return static_cast<T*>( m_Variant );
    }

    const T* operator->() const
    {
#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return static_cast<T*>( m_Variant );
    }

    T& operator*()
    {
#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return *static_cast<T*>( m_Variant );
    }

    const T& operator*() const
    {
#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return *static_cast<T*>( m_Variant );
    }

    operator T* ()
    {
        return static_cast<T*>( m_Variant );
    }

    operator const T* () const
    {
        return static_cast<T*>( m_Variant );
    }

    bool Empty()
    {
        return m_Variant == 0;
    }

    bool Clear()
    {
        return m_Variant = 0;
    }

private:

    TypeVariant* m_Variant;
};

#endif
