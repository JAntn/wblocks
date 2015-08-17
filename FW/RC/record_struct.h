#ifndef C_RECORD_STRUCT_H
#define C_RECORD_STRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class C_Record;
class C_RecordFactory;
class C_StateReader;
class C_StateWriter;

class C_RecordStruct : public C_VariantStruct
{
public:

    typedef list<C_Variant*>::const_iterator const_iterator;

    explicit C_RecordStruct( QString name, C_Variant* parent = 0 );
    ~C_RecordStruct() override;

    C_Record*                          CreateRecord( C_StateWriter& state, int position = -1 );
    C_Record*                          CreateRecord( QString name, QString value, QString class_name, int position = -1 );
    C_Record*                          CreateRecord( C_StateWriter& state, const_iterator position );
    C_Record*                          CreateRecord( QString name, QString value, QString class_name, const_iterator position );

    C_Record*                          FromIndex( int row ) const;
    C_Record*                          FromName( QString name , bool deep = false ) const;
    C_Record*                          FromId( QString record_id, bool deep = false ) const;
    int                                GetIndex( C_Record* record ) const;

    static
    C_RecordFactory*                   FactoryFromName( QString class_name );

    static
    const
    list<C_RecordFactory*>&            FactoryList() ;

    static
    void                               InitFactoryList();
    QString                            FullName();
    ATR_VALUE                          ( Name, QString )
    ATR_VALUE                          ( Flags, long )

private:

    static
    list<C_RecordFactory*>             m_FactoryList;
};


#endif // C_RECORD_STRUCT_H
