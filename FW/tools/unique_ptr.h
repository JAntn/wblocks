#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

// TypeScopePtr
// -----------------------------------------------------------------------------------------------------------
// Wraps a given pointer and behaves like it but releases its
// contents when instance leaves the scope ; similar to unique_ptr

template<typename T>
class TypeUniquePtr
{
    T* m_Ptr;

public:

    T* Ptr()
    {
        return m_Ptr;
    }

    TypeUniquePtr( T* pointer  )
    {
        m_Ptr = pointer;
    }

    ~TypeUniquePtr()
    {
        delete m_Ptr;
    }


    T* operator->()
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif

        return m_Ptr;
    }

    const T* operator->() const
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return m_Ptr;
    }

    T& operator*()
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return *m_Ptr;
    }

    const T& operator*() const
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return *m_Ptr;
    }
};

#endif // UNIQUE_PTR_H

