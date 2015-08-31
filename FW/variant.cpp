#include "FW/variant.h"
#include <QDebug>

TypeVariant::TypeVariant( TypeVariant* parent )
{
    if( parent != 0 )
        parent->m_Childreen.append( this );

    m_Parent = parent;
}

TypeVariant::~TypeVariant()
{
    if( m_Parent != 0 )
    {
        m_Parent->m_Childreen.removeOne( this );
        m_Parent = 0;
    }

    for( auto iter = m_Childreen.begin(); iter != m_Childreen.end();  )
    {
        TypeVariant* variant = *iter;
        variant->m_Parent = 0;
        delete variant;
        iter = m_Childreen.erase(iter);
    }
}

void TypeVariant::SetParent( TypeVariant* parent )
{
    if( m_Parent != 0 )
        m_Parent->m_Childreen.removeOne( this );

    if( parent != 0 )
        parent->m_Childreen.append( this );

    m_Parent = parent;
}

TypeVariant* TypeVariant::Parent() const
{
    return m_Parent;
}


