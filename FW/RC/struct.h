#ifndef STRUCT_H
#define STRUCT_H

#include "FW/tools.h"

class TypeRecord;
class TypeRecordFactory;
class TypeStateReader;
class TypeStateWriter;

class TypeStruct : public TypeVariantStruct
{
public:

    explicit TypeStruct( TypeVariant* Parent = 0 );
    ~TypeStruct() override;

    virtual TypeRecord*                          ParentRecord();
    virtual TypeStruct*                          ParentStruct();

    TypeRecord*                                  NewRecord( TypeStateWriter& state, int position = -1, TypeStruct* root = 0 );
    TypeRecord*                                  NewRecord( QString name, QString value, QString class_name, int position = -1, TypeStruct* root = 0 );
    TypeRecord*                                  NewRecord( TypeStateWriter& state, iterator position, TypeStruct* root = 0 );
    TypeRecord*                                  NewRecord( QString name, QString value, QString class_name, iterator position, TypeStruct* root = 0 );

    TypeRecord*                                  FromIndex( int row ) const;
    TypeRecord*                                  FromId( QString record_id, bool deep = false ) const;
    TypeRecord*                                  FromName(QString record_name , bool deep = false) const;

    int                                          GetIndex( TypeRecord* record ) const;

    M_VALUE                                      ( Flags, long )
};


#endif // STRUCT_H
