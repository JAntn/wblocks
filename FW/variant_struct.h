#ifndef TypeVARIANTSTRUCT_H
#define TypeVARIANTSTRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class TypeVariantStruct : public TypeVariant
{
public:

    typedef QList<TypeVariant*>::const_iterator const_iterator;
    typedef QList<TypeVariant*>::iterator iterator;

     TypeVariantStruct(TypeVariant* parent=0);
    ~TypeVariantStruct() override;

    void                                Append(TypeVariant& variant);
    void                                Insert(int position, TypeVariant& variant);
    void                                Insert(iterator position, TypeVariant& variant);
    int                                 Size() const;
    void                                Clear();

    QList<TypeVariant*>::iterator         begin();
    QList<TypeVariant*>::iterator         end();
    QList<TypeVariant*>::const_iterator   begin() const;
    QList<TypeVariant*>::const_iterator   end() const;
};

#endif // TypeVARIANTSTRUCT_H
