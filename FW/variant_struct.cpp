#include "FW/variant.h"

C_VariantStruct::C_VariantStruct(C_Variant* parent)
    : C_Variant(parent)
{
    // void
}

list<C_Variant*>::const_iterator C_VariantStruct::begin()
{
    return m_Childreen.begin();
}

list<C_Variant*>::const_iterator C_VariantStruct::end()
{
    return m_Childreen.end();
}

list<C_Variant*>::const_iterator C_VariantStruct::begin() const
{
    return m_Childreen.begin();
}

list<C_Variant*>::const_iterator C_VariantStruct::end() const
{
    return m_Childreen.end();
}

void C_VariantStruct::Append(C_Variant& node)
{
    m_Childreen.push_back(&node);
    node.m_Parent = this;
}

void C_VariantStruct::Insert(int index, C_Variant& node)
{
    auto iter = m_Childreen.begin();

    for(int count = 0; count < index; ++count) {
        ++iter;
    }

    m_Childreen.insert(iter,&node);
    node.m_Parent = this;
}

void C_VariantStruct::Clear()
{
    auto iter = m_Childreen.begin();
    while( iter != m_Childreen.end() )
    {
        delete * iter;
        iter = m_Childreen.begin();
    }

}

int C_VariantStruct::Size() const
{
    return m_Childreen.size();
}
