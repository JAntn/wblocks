#ifndef TOOLS_H
#define TOOLS_H

#include "FW/variant.h"

// Most used include files
#include <functional>
#include <QDebug>
#include <QList>
#include <QVector>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QStack>
#include <QFileDialog>
#include <QRegExp>

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

    TypeVariantPtr( const TypeVariantPtr& variant )
    {
        m_Variant = variant.m_Variant;

    }

    T& operator=( const TypeVariantPtr& variant )
    {
        m_Variant = variant.m_Variant;
        return this->operator*();
    }

    T& operator=( TypeVariant* variant )
    {
        m_Variant = variant;
        return this->operator*();
    }

    T* operator->()
    {
        return static_cast<T*>( m_Variant );
    }

    const T* operator->() const
    {
        return static_cast<T*>( m_Variant );
    }

    T& operator*()
    {
        return *static_cast<T*>( m_Variant );
    }

    const T& operator*() const
    {
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




#endif // TOOLS_H

