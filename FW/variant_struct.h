#ifndef C_VARIANTSTRUCT_H
#define C_VARIANTSTRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class C_VariantStruct : public C_Variant
{   
public:

     C_VariantStruct(C_Variant* parent=0);
    ~C_VariantStruct() override;

    void                               Append(C_Variant& node);
    void                               Insert(int position, C_Variant& node);

    int                                Size() const;
    void                               Clear();

    list<C_Variant*>::const_iterator   begin();
    list<C_Variant*>::const_iterator   end();
    list<C_Variant*>::const_iterator   begin() const;
    list<C_Variant*>::const_iterator   end() const;
};

#endif // C_VARIANTSTRUCT_H
