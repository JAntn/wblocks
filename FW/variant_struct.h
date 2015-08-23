#ifndef C_VARIANTSTRUCT_H
#define C_VARIANTSTRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class C_VariantStruct : public C_Variant
{
public:

    typedef QList<C_Variant*>::const_iterator const_iterator;
    typedef QList<C_Variant*>::iterator iterator;

     C_VariantStruct(C_Variant* parent=0);
    ~C_VariantStruct() override;

    void                                Append(C_Variant& variant);
    void                                Insert(int position, C_Variant& variant);
    void                                Insert(iterator position, C_Variant& variant);
    int                                 Size() const;
    void                                Clear();

    QList<C_Variant*>::iterator         begin();
    QList<C_Variant*>::iterator         end();
    QList<C_Variant*>::const_iterator   begin() const;
    QList<C_Variant*>::const_iterator   end() const;
};

#endif // C_VARIANTSTRUCT_H
