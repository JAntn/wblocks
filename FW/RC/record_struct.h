#ifndef TypeRECORD_STRUCT_H
#define TypeRECORD_STRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class TypeRecord;
class TypeRecordFactory;
class TypeStateReader;
class TypeStateWriter;

class TypeRecordStruct : public TypeVariantStruct
{
public:

    explicit TypeRecordStruct( QString name, TypeVariant* parent = 0 );
    ~TypeRecordStruct() override;

    TypeRecord*                          CreateRecord( TypeStateWriter& state, int position = -1, TypeRecordStruct* root = 0 );
    TypeRecord*                          CreateRecord( QString name, QString value, QString class_name, int position = -1, TypeRecordStruct* root = 0 );
    TypeRecord*                          CreateRecord( TypeStateWriter& state, iterator position, TypeRecordStruct* root = 0 );
    TypeRecord*                          CreateRecord( QString name, QString value, QString class_name, iterator position, TypeRecordStruct* root = 0 );

    TypeRecord*                          FromIndex( int row ) const;
    TypeRecord*                          FromName( QString name , bool deep = false ) const;
    TypeRecord*                          FromId( QString record_id, bool deep = false ) const;

    int                                GetIndex( TypeRecord* record ) const;
    TypeRecord*                          FromFullName( QString name ) const;
    QString                            FullName();

    static TypeRecordFactory*                   FactoryFromName( QString class_name );
    static const QList<TypeRecordFactory*>&     FactoryList() ;
    static void                               InitFactoryList();

    M_VALUE                            ( Name, QString )
    M_VALUE                            ( Flags, long )

private:

    static QList<TypeRecordFactory*>             m_FactoryList;
};


#endif // TypeRECORD_STRUCT_H
