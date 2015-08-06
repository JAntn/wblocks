#include "FW/variant.h"
#include <QDebug>

C_Variant::C_Variant(C_Variant* parent)
{
    if( parent != 0 )
    {
        parent->m_Childreen.push_back(this);
    }

    m_Parent = parent;
}

C_Variant::~C_Variant()
{
    if( m_Parent != 0 )
    {
        m_Parent->m_Childreen.remove(this);
        m_Parent = 0;
    }

    auto iter = m_Childreen.begin();
    while(iter != m_Childreen.end())
    {
        delete *iter;
        iter = m_Childreen.begin();
    }
}

void C_Variant::SetParent(C_Variant* parent)
{
    if( m_Parent == parent)
        return;

    if( m_Parent != 0 )
    {
        m_Parent->m_Childreen.remove(this);
    }

    if( parent != 0 )
    {
        parent->m_Childreen.push_back(this);
    }

    m_Parent = parent;
}

C_Variant* C_Variant::Parent() const
{
    return m_Parent;
}


