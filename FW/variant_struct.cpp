#include "FW/variant.h"

C_VariantStruct::C_VariantStruct( C_Variant* parent ):
    C_Variant( parent )
{
    // void
}

C_VariantStruct::~C_VariantStruct()
{
    // void
}

QList<C_Variant*>::iterator C_VariantStruct::begin()
{
    return m_Childreen.begin();
}

QList<C_Variant*>::iterator C_VariantStruct::end()
{
    return m_Childreen.end();
}

QList<C_Variant*>::const_iterator C_VariantStruct::begin() const
{
    return m_Childreen.begin();
}

QList<C_Variant*>::const_iterator C_VariantStruct::end() const
{
    return m_Childreen.end();
}

void C_VariantStruct::Append( C_Variant& node )
{
    m_Childreen.append( &node );
    node.m_Parent = this;
}

void C_VariantStruct::Insert( int index, C_Variant& node )
{
    m_Childreen.insert( index, &node );
    node.m_Parent = this;
}

void C_VariantStruct::Insert( iterator iter, C_Variant& node )
{
    if( iter == begin() )
        m_Childreen.push_front( &node );

    else if( iter == end() )
        m_Childreen.push_back( &node );

    else
        m_Childreen.insert( --iter, &node );

    node.m_Parent = this;
}

void C_VariantStruct::Clear()
{
    for( auto iter = m_Childreen.begin(); iter != m_Childreen.end(); )
    {
        auto value = *iter;
        value->m_Parent = 0;
        delete value;
        iter = m_Childreen.erase( iter );
    }
}

int C_VariantStruct::Size() const
{
    return m_Childreen.size();
}
