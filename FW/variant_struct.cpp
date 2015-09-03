#include "FW/variant_struct.h"

TypeVariantStruct::TypeVariantStruct( TypeVariant* parent ):
    TypeVariant( parent )
{
    // void
}

TypeVariantStruct::~TypeVariantStruct()
{
    // void
}

QList<TypeVariant*>::iterator TypeVariantStruct::begin()
{
    return m_Childreen.begin();
}

QList<TypeVariant*>::iterator TypeVariantStruct::end()
{
    return m_Childreen.end();
}

QList<TypeVariant*>::const_iterator TypeVariantStruct::begin() const
{
    return m_Childreen.begin();
}

QList<TypeVariant*>::const_iterator TypeVariantStruct::end() const
{
    return m_Childreen.end();
}

void TypeVariantStruct::Append( TypeVariant& variant )
{
    m_Childreen.append( &variant );
    variant.m_Parent = this;
}

void TypeVariantStruct::Insert( int index, TypeVariant& variant )
{
    m_Childreen.insert( index, &variant );
    variant.m_Parent = this;
}

void TypeVariantStruct::Insert( iterator iter, TypeVariant& variant )
{
    if( iter == begin() )
        m_Childreen.push_front( &variant );

    else if( iter == end() )
        m_Childreen.push_back( &variant );

    else
        m_Childreen.insert( --iter, &variant );

    variant.m_Parent = this;
}

void TypeVariantStruct::Clear()
{
    for( auto iter = m_Childreen.begin(); iter != m_Childreen.end(); )
    {
        TypeVariant* variant = *iter;
        variant->m_Parent = 0;
        delete variant;
        iter = m_Childreen.erase( iter );
    }
}

int TypeVariantStruct::Size() const
{
    return m_Childreen.size();
}
