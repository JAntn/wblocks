#ifndef C_RECORD_STRUCT_H
#define C_RECORD_STRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class C_Record;
class C_RecordFactory;
class C_DataState;
class C_DataState;

class C_RecordStruct : public C_VariantStruct
{
public:

    explicit C_RecordStruct( QString name, C_Variant* parent = 0 );
    ~C_RecordStruct() override;

    C_Record*                          CreateRecord( C_DataState& state, int position = -1 );
    C_Record*                          CreateRecord( QString name, QString value, QString class_name, int position = -1 );

    C_Record*                          FromIndex( int row ) const;
    C_Record*                          FromName( QString name ) const;
    C_Record*                          FromId( QString record_id ) const;
    int                                GetIndex( C_Record* record ) const;

    static
    C_RecordFactory*                   FactoryFromName( QString class_name );

    static
    const
    list<C_RecordFactory*>&            FactoryList() ;

    static
    void                               InitFactoryList();

    C_VALUE                            ( Name, QString )
    C_VALUE                            ( Flags, long )

private:

    static
    list<C_RecordFactory*>             m_FactoryList;
};


#endif // C_RECORD_STRUCT_H
