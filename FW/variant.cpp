#include "FW/variant.h"
#include <QDebug>

C_Variant::C_Variant( C_Variant* parent )
{
    if( parent != 0 )
        parent->m_Childreen.append( this );

    m_Parent = parent;
}

C_Variant::~C_Variant()
{
    if( m_Parent != 0 )
    {
        m_Parent->m_Childreen.removeOne( this );
        m_Parent = 0;
    }

    for( auto iter = m_Childreen.begin(); iter != m_Childreen.end();  )
    {
        auto value = *iter;
        value->m_Parent = 0;
        delete value;
        iter = m_Childreen.erase(iter);
    }
}

void C_Variant::SetParent( C_Variant* parent )
{
    if( m_Parent != 0 )
        m_Parent->m_Childreen.removeOne( this );

    if( parent != 0 )
        parent->m_Childreen.append( this );

    m_Parent = parent;
}

C_Variant* C_Variant::Parent() const
{
    return m_Parent;
}


